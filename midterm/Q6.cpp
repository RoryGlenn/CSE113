6a) 
    Yes, the sequential sequence of object method calls will be t0 == 1 and t1 == 2 and t2 == 3 and t3 == 4. Following program order we can execute the instructions as such:
    Thread 0: q0.enq(1)
    Thread 0: q0.enq(2)
    Thread 0: q0.enq(3)
    Thread 1: int t0 = q0.deq()
    Thread 1: int t1 = q0.deq()
    Thread 1: int t2 = q0.deq()
    Thread 1: int t3 = q0.deq()
    Thread 0: q0.enq(4)

6b) 
    Yes, the values can be such by executing the instructions as such:
    Thread 0: q0.enq(1);
    Thread 2: int t0 = q0.deq();
    Thread 2: int t1 = q1.deq();
    Thread 1: q1.enq(1);
    Add more explanation
    is all that is left

6c) 
    Yes, the values can be such by executing the instructions as such:
    Thread 0: q0.enq(1);
    Thread 2: int t0 = q0.deq();
    Thread 2: int t1 = q1.deq();
    Thread 1: q1.enq(1);
    Thread 3: int t2 = q1.deq()
    Thread 3: int t3 = q0.deq()