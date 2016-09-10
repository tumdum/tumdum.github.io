---
layout: post
date: 2016-03-11
title: "Type level programming"
---

While watching [Typelevel Programming 101: The Subspace of Scala](https://youtu.be/_-J4YRI1rAw) I was reminded of Peano numbers. It's a way to encode natural numbers which is derived from [Peano axioms](https://en.wikipedia.org/wiki/Peano_axioms). Which got me thinking - since I don't know how long I had a feeling that there is almost mechanical translation from subset of Haskell programs to C++ meta programs. Specifically I had in mind programs which use only natural numbers and lists. So let's find out if such relationship is real.

In the rest of the post I will always start with Haskell version, followed by C++ version.
## Encoding natural numbers
To encode natural numbers let's start with Peano axioms 1 and 6.  Expressed as Haskell programs we have:

{% highlight haskell %}
data Number = 
    Zero | 
    Next Number
    deriving (Show, Eq)
{% endhighlight %}

This declares new type `Number` with two constructors. One niladic representing number 0 and called `Zero`. Second one is a successor function, and takes one argument also of type `Number`. 

So how do we do this as a type level program in C++? This will require one type definition and one type template definition.

{% highlight c++ %}
struct Zero { enum { value = 0 }; }; 

template <typename Nat>                                                         
struct Next { enum { value = 1 + Nat::value }; };
{% endhighlight %}
To make it easier to test this number representations, lets define helper function to easily convert integers to Peano naturals. First Haskell:

{% highlight haskell %}
v :: Int -> Number
v 0 = Zero
v n = Next (v (n -1))
{% endhighlight %}
and similarly C++:
{% highlight c++ %}
template <int i>
struct _V { using type = Next<typename _V<i-1>::type>; };

template <>
struct _V<0> { using type = Zero; };

template <int i>
using V = typename _V<i>::type;
{% endhighlight %}
In both languages there is special case for zero, and general recurrence for all other values/types. In case of C++ I've added helper alias to make it easier to use.

We can test Haskell part in ghci:

{% highlight haskell %}
> let one  = Next Zero
> let two  = Next one
> let five = Next (Next (Next two))
> let six  = v 6
{% endhighlight %}
And C++ can be declared as:
{% highlight c++ %}
using One  = Next<Zero>;
using Two  = Next<One>;
using Five = Next<Next<Next<Two>>>;
using Six  = V<6>;
{% endhighlight %}
## Arithmetic
Now that we have numbers, we can define basic [arithmetic](https://en.wikipedia.org/wiki/Peano_axioms#Arithmetic) operations.

Starting with [addition](https://en.wikipedia.org/wiki/Peano_axioms#Addition), we just follow definition from Wikipedia:
{% highlight haskell %}
add :: Number -> Number -> Number
add Zero       rhs = rhs
add (Next lhs) rhs = Next (add lhs rhs)
{% endhighlight %}
This is very short in Haskell and very straightforward. In type level C++ it's only slightly longer:
{% highlight c++ %}
template <typename Lhs, typename Rhs> struct _Add;

template <typename Rhs> struct _Add<Zero, Rhs>
{
        using type = Rhs;
};

template <typename Lhs, typename Rhs> struct _Add<Next<Lhs>, Rhs>
{
        using type = Next<typename _Add<Lhs, Rhs>::type>;
};

template <typename LHS, typename RHS> using Add = typename _Add<LHS, RHS>::type;
{% endhighlight %}

Testing in Haskell repl shows that it seems to be working:
{% highlight haskell %}
> let two = v 2
> let five = v 5
> five == two
False
> let four = v 4
> (add four four) == (add five (add two (Next Zero)))
True
{% endhighlight %}
In C++ we can express similar tests as:
{% highlight c++ %}
static_assert(!std::is_same<Five, Two>::value, "");
static_assert(std::is_same<Add<Four, Four>, Add<Five, Add<Two, One>>>::value, "");
{% endhighlight %}

Now that we have addition, [multiplication](https://en.wikipedia.org/wiki/Peano_axioms#Multiplication) should be easy. First Haskell:
{% highlight haskell %}
mul :: Number -> Number -> Number
mul Zero        _   = Zero
mul (Next lhs)  rhs = add rhs (mul lhs rhs)
{% endhighlight %}
and C++:
{% highlight c++ %}
template <typename Lhs, typename Rhs> struct _Mul;

template <typename Rhs> struct _Mul<Zero, Rhs>
{
        using type = Zero;
};

template <typename Lhs, typename Rhs> struct _Mul<Next<Lhs>, Rhs>
{
        using tmp  = typename _Mul<Lhs, Rhs>::type;
        using type = typename _Add<Rhs, tmp>::type;
};

template <typename LHS, typename RHS> using Mul = typename _Mul<LHS, RHS>::type;
{% endhighlight %}
Testing in Haskell repl:
{% highlight haskell %}
> let six = v 6
> let seven = v 7
> (v 42) == (mul six seven)
True
{% endhighlight %}
And in C++:
{% highlight c++ %}
using Six   = V<6>;
using Seven = V<7>;
static_assert(std::is_same<V<42>, Mul<Six, Seven>>::value, "");
{% endhighlight %}
Last thing we need to have usable definition of numbers is order definition. Obviously zero is less then any non zero natural number. Additionally any two numbers are in the same order as their successors. Given this, we can derive clear Haskell implementation:
{% highlight haskell %}
less :: Number -> Number -> Bool
less Zero       (Next _)   = True
less (Next _)   Zero       = False
less Zero       Zero       = False
less (Next lhs) (Next rhs) = less lhs rhs
{% endhighlight %}
And corresponding C++ version is somewhat more involved:
{% highlight c++ %}
template <typename LHS, typename RHS> struct _Less;

template <typename RHS> struct _Less<Zero, Next<RHS>>
{
        using type = std::true_type;
};

template <typename LHS> struct _Less<Next<LHS>, Zero> 
{
        using type = std::false_type;
};

template <> struct _Less<Zero, Zero> 
{
        using type = std::false_type;
};

template <typename LHS, typename RHS> struct _Less<Next<LHS>, Next<RHS>>
{
        using type = typename _Less<LHS, RHS>::type;
};

template <typename LHS, typename RHS> using Less = typename _Less<LHS, RHS>::type;
{% endhighlight %}
Testing in Haskell repl:
{% highlight haskell %}
> less (v 7) (v 8)
True
> less (v 9) (v 8)
False
> less (v 9) (v 9)
False
{% endhighlight %}
Similar type level tests in C++:
{% highlight c++ %}
static_assert(std::is_same<std::true_type, Less<V<7>, V<8>>>::value, "");
static_assert(!std::is_same<std::true_type, Less<V<9>, V<8>>>::value, "");
static_assert(!std::is_same<std::true_type, Less<V<9>, V<9>>>::value, "");
{% endhighlight %}
That is already quite a lot of code, so let's stop here and continue in next post with lists, folds and sorting. For the impatient, full source is on [bitbucket](https://bitbucket.org/tumdum/typelevel101/).
