# Programming Assignment Instructions:
We will be using GNU C++ Compiler (g++)

**Option 1:**
If already downloaded run...
<br>
g++ --version

**Option 2:**
If needing to download run...
<br>
sudo apt update
<br>
sudo apt install g++
<br>
g++ --version

Once correctly installed download the files and then run the following codes.
(Make sure you are in the correct folder when running)

**1. Network Topology**<br>
g++ Topology.cc -o top
<br>
./top

**2. QuickSort and MergeSort**<br>
g++ QuickandMerge.cc -o quickmerge
<br>
./quickmerge

**3. Heap Bottom Up**<br>
g++ HeapBottomUp.cc -o heap
<br>
./heap

**4. Horspool String Matching**<br>
g++ Horspool.cc -o hor
<br>
./hor

**5. Floyd's Algorithm**<br>
g++ Floyd.cc -o floyd
<br>
./floyd
<br><br><br>



**Here is how the inputs should be formulated:**
<br>
**1. Network Topology**
<br>
The adjacency matrix comprised of only "0" or "1" **NOT** separated by spaces
<br>
ex)<br>
01111<br>
10111<br>
11011<br>
11101<br>
11110<br>
<br>
**2. QuickSort and MergeSort**
<br>
A list of floating point numbers separated by spaces
<br>
ex)<br>
82.1 23.4 67.8 45.2 99.5 12.3 3.7 88.4 56.1 42.9 77.3 19.5 2.1 39.7 65.5 8.2 97.6 30.3 71.2 55.8
<br>
<br>
**3. Heap Bottom Up**
<br>
The first line contains the number of keys and the second contains the unsorted integers separated by spaces<br>
ex)<br>
15<br>
21 35 10 5 99 18 12 6 3 1 77 44 20 8 30
<br>
<br>
**4. Horspool String Matching**
<br>
The first line contains the pattern, the second line contains the text. **CANNOT** use upper case letters. 
<br>
ex)<br>
hot<br>
this is a hot a pepper
<br><br>
**5. Floyd's Algorithm**
<br>
The file contains the distance matrix of floats separated by spaces. Use a really high number to represent infinity e.g.(999.9)
<br>ex)<br>
0.0 3.2 999.9 7.5<br>
8.1 0.0 2.4 999.9<br>
5.6 999.9 0.0 1.3<br>
2.2 999.9 999.9 0.0<br>
