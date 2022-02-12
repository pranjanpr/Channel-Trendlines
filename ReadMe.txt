Directions to compile and get parallel support and resistance trendline plots

1. Make a virtualenv and install "requirements.txt" in it.

2. Paste the test cases to evaluate in "test.txt". Eg. format is already present there.

3. Then run "python gate_data.py"
	Please note that I have converted the time format to UNIX format

4. This will make csv files corresponding to each test case fetched from gate.io.
   This will also create one "input.txt" file and few empty "output.txt" files depending on number of test cases.

5. Now run the "crypto.cpp" file. It should automatically take "input.txt" as input and paste the data obtained for each test case in "output_test_number.txt" file.
	Please edit the path of the folder in "folder_str" by editing the "crypto.cpp" if it does not works.

6. Once the "output.txt" files are populated, run "python plot_data.py". It will require just the count of test cases. It will plot the trendlines using plotly.


#Main core for finding the trendlines is in "crypto.cpp"
	1. Firstly I used sliding window technique to find trendlines for each threshold number of candlesticks.
	2. Suppose I have considered 25(threshold) number of candlesticks.
	3. It will find out the points of upper convex hull of the candlesticks using "high".
	4. Then it will find out the points of lower convex hull using "low".
	5. Now on the evaluated upper convex hull, the program will try to find a straight line passing through 3 points between max(open, close) and "high" of points on convex hull.
	6. Once we get a possible line, we add it in "slopes" vector.
	7. then we try to draw a line parallel to the already found line on lower convex hull, going through 3 points between min(open, close) and "low".
	8. Once we get such line, we add both lines to "final_ans" vector.
	9. This "final_ans" vector will go on for every sliding window.
	10. The results of this test case would then be directed to corresponding output files.
