---
layout: post
date: 2016-02-08
title: "Strong types and testing - in Go"
---

This is reimplementation of Haskell code from [bitemyapp](http://bitemyapp.com/posts/2014-11-18-strong-types-and-testing.html), which itself was inspired by [levinotik](http://levinotik.com/strong-types-and-their-impact-on-testing/). Obviously Go has much simpler type system and some of the constructs in Haskell are not possible to express in it. The most important of those are sum types and purity. Yet it is still possible to express quite a lot in Go.

bitemyapp starts with declaring simplest structure to express email, and immediately notices that having all fields to be of type *string* is not the best approach. In Go such a struct would be:

```go
type Email struct {
	toAddress     string
	fromAddress   string
	emailBody     string
	recipientName string
}
```
Having separate types for each field will make it hard to make a mistake when constructing email. Just like in Haskell, it is easy in Go:
```go
type (
	ToAddress     string
	FromAddress   string
	EmailBody     string
	RecipientName string
)

type Email struct {
	toAddress     ToAddress
	fromAddress   FromAddress
	emailBody     EmailBody
	recipientName RecipientName
}
```
bitemyapp tests his code in repl, which we don't have in Go - let's write one unit test:
```go
func TestInitialization(t *testing.T) {
	to := ToAddress("levi@startup.com")
	from := FromAddress("chris@website.org")
	body := EmailBody("hi!")
	name := RecipientName("Levi")

	/*
		email := Email{
			ToAddress:     from,
			FromAddress:   to,
			EmailBody:     body,
			RecipientName: name,
		}

		Error:
		./email_test.go:12: cannot use from (type FromAddress) as type ToAddress in field value
		./email_test.go:13: cannot use to (type ToAddress) as type FromAddress in field value
	*/

	_ = Email{
		To:        to,
		From:      from,
		Body:      body,
		Recipient: name,
	}
}
```
This is still basically the same as Haskell.

Next thing bitemyapp mentions is making this email type abstract. In Haskell that means exporting only type without any way to access its data or construct it from outside of module. Hiding constructor in Go is easy - it's enough to change `Email` to `email` to makes it private. But in contrast to Haskell, in Go it would be still possible to access members of values of that type. To have complete encapsulation (control both construction and data access) we will export only interface which email will satisfy:
```go
type email struct {
	To        ToAddress
	From      FromAddress
	Body      EmailBody
	Recipient RecipientName
}

func (e email) ToAddress() ToAddress         { return e.To }
func (e email) FromAddress() FromAddress     { return e.From }
func (e email) EmailBody() EmailBody         { return e.Body }
func (e email) RecipientName() RecipientName { return e.Recipient }

type Email interface {
	ToAddress() ToAddress
	FromAddress() FromAddress
	EmailBody() EmailBody
	RecipientName() RecipientName
}
```
Next comes smart constructor. To validate email addresses we will use `net/mail`:

```go
type (
	ErrToAddressDidntParse   struct{ reason error }
	ErrFromAddressDidntParse struct{ reason error }
)

func (e ErrToAddressDidntParse) Error() string {
	return "'To' address didn't parse: " + e.reason.Error()
}

func (e ErrFromAddressDidntParse) Error() string {
	return "'From' address didn't parse: " + e.reason.Error()
}

func NewEmail(to ToAddress, from FromAddress, body EmailBody, name RecipientName) (Email, []error) {
	errors := []error{}
	if err := validateAddress(string(to)); err != nil {
		errors = append(errors, ErrToAddressDidntParse{err})
	}
	if err := validateAddress(string(from)); err != nil {
		errors = append(errors, ErrFromAddressDidntParse{err})
	}
	if len(errors) > 0 {
		return nil, errors
	}
	return &email{To: to, From: from, Body: body, Recipient: name}, errors
}

func validateAddress(address string) error {
	_, err := mail.ParseAddress(address)
	return err
}
```
Here we start to diverge from Haskell, at least in terms of succinctness. Thanks to thy way instance of Applicative typeclass for Maybe is [defined](http://hackage.haskell.org/package/base-4.8.2.0/docs/src/GHC.Base.html#line-633), it is possible to express smart constructor in much shorter way. Additionally since Go has no sum types we lose type information in return value, by returning list of any errors. And finally to make this as close to Haskell as possible we diverge from Go idiom of returning error value and return list of errors. Since we still have no repl, here is a test for smart constructor:
```go
func TestSmartConstructor(t *testing.T) {
	if _, err := NewEmail(ToAddress("PLAID"), FromAddress("TROLOLOL"), body, name); len(err) == 0 {
		t.Fatal("Malformed email in 'To' field was not detected")
	} else {
		log.Println(err)
	}
	if _, err := NewEmail(to, from, body, name); len(err) > 0 {
		t.Fatalf("Correct invocation failed: '%v'", err)
	}
}
```
Lastly we add a way to parse email out of json. This is done with `encoding/json` and whole code is available at [bitbucket.org](http://bitbucket.org/tumdum/email).
