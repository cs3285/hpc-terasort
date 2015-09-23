#CSE 6220 Distributed Sorting -- Terasort

In this lab, your task is to implement a distributed sorting algorithm along the lines discussed in the lesson videos.  Your design should be based on the assumption that the data will *not* fit in the physical memory of any one computer in your cluster but that it *will* fit in the union of all the physical memories.  This assumption makes your task slightly different from classical 
[distributed disk sorting benchmarks](http://sortbenchmark.org/), but many of the same principles apply.

##Getting Started
Begin by obtaining the starter code from the github repository.

<pre><code>
	git clone https://github.gatech.edu/sb300/oms-hpc-lab4.git
</code></pre>

Note that this is the [GT github server](https:github.gatech.edu), so you will need to authenticate with your GT credentials.

Optionally, you may choose use a git hosting service for your code.  As always, please **do not make your repository public** on Github or another git hosting service.  Anyone will be able to see it.  If you feel the need to use a hosting service for your project, please keep your repository private.  Your GT account allows you to create free private repositories on [the GT github server](https:github.gatech.edu).

##Programming
The data type you will sorting is similar to the one used in [Hadoop's Terasort benchmark](https://hadoop.apache.org/docs/current/api/org/apache/hadoop/examples/terasort/package-summary.html#package_description).  It consists of a 10 byte key and an 88 bytes value.  Procedures for input/output and comparison of these records are provided for you in the **terarec.h** and **terarec.c** files.  Your only task is to complete the implementation of the terasort function, which has the signature

<pre><code>
	void terasort(terarec_t *local_data, int local_len, terarec_t **sorted_data, int* sorted_counts, long* sorted_displs);
</code></pre>

Here local_data is the data initially stored in memory at the calling node and local_len is the number of elements in this array.  The remaining parameters are for return values.  The arrays sorted_count and sorted_displs indicate the length and displacement of each node's sorted segment within the whole.  Thus, the data returned to node rank represents the sorted sequence starting at sorted_displs[rank] and has length sorted_count[rank].  The data itself is returned in \*sorted_data, memory which the terasort function itself allocates.

An example of the function's usage can be found in the **terasort_main.c** and the **terametrics.c** files.

##Measuring Performance
In addition to illustrating the usage of the terasort function, the **terasort_main.c** file also measures the running time of the code.  Profile your code, experiment with different strategies, and come up with the fastest implementation you can.  Performance tests will be a large part of your evaluation.You are encouraged share your ideas and results on the Piazza forum.  Good luck!

## Submitting Your Code
When you have finished and tested your implementations, please submit them to the [Udacity site](https://www.udacity.com/course/viewer#!/c-ud281/l-5154708552/m-5140272747), which will make a quick test for correctness.  After the deadline, the TAs will pull the code and perform some timing runs to confirm that your implementation is efficient, and compare your results to those of other students.


