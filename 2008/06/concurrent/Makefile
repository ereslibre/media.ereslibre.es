#
# By Rafael Fernández López, 2008.
#
# concurrent1 will execute code in 10 different threads, but they
# will be executed one after the other, since the waiting is done
# just after the last is started and just before the next is started.
#
# concurrent2 will execude code in 10 different threads, and there are
# some special threads, that will take for it more time to complete: odd ones.
# You will see how the rest of them are being executed while odd threads are
# still on the processor, competing for it.
#
# concurrent3 will do the same as concurrent2, but assuring the output of the
# odd threads themselves is ordered between them, that means, this output for
# example is correct: 0, 2, 4, 6, 8, 1, 3, 5, 7, 9, while this other isn't:
#                     0, 2, 4, 6, 8, 1, 5, 3, 7, 9.
#
concurrent1 : Makefile concurrent.cpp
	$(CXX) $(CXXFLAGS) -lpthread concurrent.cpp -o ${@}

concurrent2 : Makefile concurrent.cpp
	$(CXX) $(CXXFLAGS) -DWAIT_AFTER -lpthread concurrent.cpp -o ${@}

concurrent3 : Makefile concurrent.cpp
	$(CXX) $(CXXFLAGS) -DWAIT_AFTER -DORDER_ODD_THREADS_EXIT -lpthread concurrent.cpp -o ${@}
