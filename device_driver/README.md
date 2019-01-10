Name: Arjun Bhatnagar
Topic: OS submission 4
B Number: B00759636
PART A:
1. 	Output of the tried code:
	
	[622755.924872] <1>Hello world 1.
	[622755.924874] <1> your output from display function 
	[622755.924884] <1> your sum is 30 
	[622755.924884] <1> your output is (a+b)
	[622860.367398] Goodbye world 1.

5. mkfifo fifo1
	prw-rw-r-- 1 bhatnagar_arjun191994 bhatnagar_arjun191994 0 Nov 13 00:25 fifo1
	
	PART B:

1. When running the user level code following outputs where observed:
   
   Output for running the consumer_number.
	
	Number read: 166630 Bytes read: 4
	Number read: 166631 Bytes read: 4
	Number read: 166632 Bytes read: 4
	Number read: 166633 Bytes read: 4
	Number read: 166634 Bytes read: 4
	Number read: 166635 Bytes read: 4

   Output for running the producer_number.
   
	Writing: 166630Bytes written: 4
	Writing: 166631Bytes written: 4
	Writing: 166632Bytes written: 4
	Writing: 166633Bytes written: 4	
	Writing: 166634Bytes written: 4
	Writing: 166635Bytes written: 4

2.a. On preempting the producer, since there is nothing to read as there is no data to read or buffer is empty.
	
	 error reading ret=0 errno=0 perror: Success
	 error reading ret=0 errno=0 perror: Success
	 error reading ret=0 errno=0 perror: Success
	 error reading ret=0 errno=0 perror: Success
	 error reading ret=0 errno=0 perror: Success
	 
b.	On preempting the consumer, the producer throws error messages as the code is handling the sigpipe signal which prevents the consumer from being preempted but since there is no one to consume the data.
	
	 error writing ret=-1 errno=32 perror: Broken pipe
	 error writing ret=-1 errno=32 perror: Broken pipe
	 error writing ret=-1 errno=32 perror: Broken pipe
	 error writing ret=-1 errno=32 perror: Broken pipe
	 error writing ret=-1 errno=32 perror: Broken pipe
	 error writing ret=-1 errno=32 perror: Broken pipe
	 error writing ret=-1 errno=32 perror: Broken pipe

6. On running multiple combinations of producers and consumers.
   I was able to observe that whenever that
	1) consumer was switching between the outputs from producer
	2) and consuming data one at a time and no data was consumed twice.
   Since this is a pipe there are chances that one of the consumer stays ideal for a longer than usual time this can cause latency in the execution of the code.   

PART C Plan:

1. I plan to write a namedpipe that creates a FIFO data structure which can be an array, used for communication.
2. Then pass the output of the consumer to the namedpipe. After passing the data to the structure. I would use the producer to read the data from it. This can be done by redirecting the file IO.
 3. This data structure uses Semaphores to synchronize the data access.
 4. There is also a need of a lock on the object to prevent the data corruption due to multiple consumer accessing the data structure.
 5. Using miscellaneous character device will help me create /dev/numpipe. That can easily pass values from one part of the server.

I will use the above component to implement the namedpipe.
