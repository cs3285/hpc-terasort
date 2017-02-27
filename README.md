#CSE 6220 Distributed Sorting -- Terasort

In this lab, your task is to implement a distributed sorting algorithm along the lines discussed in the lesson videos.  Your design should be based on the assumption that the data will *not* fit in the physical memory of any one computer in your cluster but that it *will* fit in the union of all the physical memories.  This assumption makes your task slightly different from classical 
[distributed disk sorting benchmarks](http://sortbenchmark.org/), but many of the same principles apply.

##Getting Started
Begin by obtaining the starter code from the github repository.

<pre><code>
    git clone --recursive https://github.gatech.edu/omscse6220/lab4.git
</code></pre>

Note that this is the [GT github server](https://github.gatech.edu), so you will need to authenticate with your GT credentials.

Optionally, you may choose use a git hosting service for your code.  As always, please **do not make your repository public** on Github or another git hosting service.  Anyone will be able to see it.  If you feel the need to use a hosting service for your project, please keep your repository private.  Your GT account allows you to create free private repositories on [the GT github server](https://github.gatech.edu).

##Programming
The data type you will sorting is similar to the one used in [Hadoop's Terasort benchmark](https://hadoop.apache.org/docs/current/api/org/apache/hadoop/examples/terasort/package-summary.html#package_description).  It consists of a 10 byte key and an 88 bytes value.  Procedures for input/output and comparison of these records are provided for you in the **terarec.h** and **terarec.c** files.  Your only task is to complete the implementation of the terasort function, which has the signature

<pre><code>
	void terasort(terarec_t *local_data, int local_len, terarec_t **sorted_data, int* sorted_counts, long* sorted_displs);
</code></pre>

Here local_data is the data initially stored in memory at the calling node and local_len is the number of elements in this array.  The remaining parameters are for return values.  The arrays sorted_count and sorted_displs indicate the length and displacement of each node's sorted segment within the whole.  Thus, the data returned to node rank represents the sorted sequence starting at sorted_displs[rank] and has length sorted_count[rank].  The data itself is returned in \*sorted_data, memory which the terasort function itself allocates.

An example of the function's usage can be found in the **terasort_main.c**.

##Testing Your Code and Measuring Performance
The **terasort_main.c** file illustrates the usage of the terasort function. You can add timers inside **terasort_main.c** to profile your code, experiment with different strategies, and come up with the fastest implementation you can.  Performance tests will be a large part of your evaluation.You are encouraged share your ideas and results on the Piazza forum.  Good luck!

An example how to test your code locally would be:
<pre><code>
$ make clean
$ make teragen teravalidate
$ make terasort
$ mpirun -np 4 ./teragen -c 10000
$ mpirun -np 4 ./terasort
$ mpirun -np 4 ./teravalidate
</code></pre>

A slurm job *example.sub* is included for testing on Deepthought.

## Deliverables
The deliverables for this lab are as follows:

* terasort.c

Please do not make any changes to the *Makefile*. If you include any additional headers or libraries, please make sure they compile as-is on the VM, Deepthought and through Bonnie.

## Submitting Your Code
Submitting Your Code

Once you have completed and tested your implementations, please submit using the submit.py script,
<pre><code>
python submit.py
</code></pre>
which will do a quick correctness test. You may submit as many times as you like before the deadline. At the deadline, the TA will download the code and perform some timing runs. These results along with a manual inspection of the code will determine your grade.


