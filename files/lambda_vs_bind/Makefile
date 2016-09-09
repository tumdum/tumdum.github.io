all: boost std lambda boost_lambda
	ls -l *.o > $(OUT_FILE).txt
	nm --size-sort --demangle lambda.o > $(OUT_FILE)_lambda_symbols.txt
	nm --size-sort --demangle std_bind.o > $(OUT_FILE)_std_bind_symbols.txt
	nm --size-sort --demangle boost_bind.o > $(OUT_FILE)_boost_bind_symbols.txt
	nm --size-sort --demangle boost_lambda.o > $(OUT_FILE)_boost_bind_symbols.txt
	rm *.o

boost: boost_bind.cc
	$(CC) $(CXX_FLAGS) -c boost_bind.cc

std: std_bind.cc
	$(CC) $(CXX_FLAGS) -c std_bind.cc

lambda: lambda.cc
	$(CC) $(CXX_FLAGS) -c lambda.cc

boost_lambda: boost_lambda.cc
	$(CC) $(CXX_FLAGS) -c boost_lambda.cc
