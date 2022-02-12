#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>


#define Int long long
#define m 1000000007

using namespace std;

void read_file(string fname, vector<vector<float>>&v, vector<vector<string>>&content){

	
	vector<string> row;
	string line, word;
 
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
 	
	for(int i=1;i<content.size();i++)
	{
		vector<float>tmp;
		tmp.clear();

		for(int j=2; j<content[i].size(); j++)
		{
			//cout<<content[i][j]<<" ";
			
			tmp.push_back(stof(content[i][j]));
		}
		//cout << endl;
		v.push_back(tmp);
	}
	//first line is time-volume-close-high-low-open

	return;
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	
//#ifndef ONLINE_JUDGE
    	string folder_str = "C:/Users/LENOVO/Desktop/crypto/";
	 	freopen((folder_str + "input.txt").c_str(), "r", stdin);
	 	//freopen("output.txt", "w", stdout);
//#endif


	 	string base_str = "C:/Users/LENOVO/Desktop/crypto/";
	 	cin >> base_str;

	 	int test_cases = 0;
	 	cin >> test_cases;
	 	//cout << test_cases << endl;
	 	Int threshold = 0;
	 	cin >> threshold;
	 	//cout << threshold << endl;

	 for(int iter = 0; iter < test_cases; iter ++){
	 	string inp_str = "";
	 	cin >> inp_str;
	 	//cout << inp_str << endl;
	 	vector<vector<float>>v;
	 	vector<vector<string>>content;

	 	
	 	freopen((base_str + "output" + to_string(iter+1) + ".txt").c_str(), "w", stdout);

	 	read_file(base_str + inp_str, v, content);
	 	

	 	vector<vector<float>>final_ans;

	 	for(Int i = 0; i + threshold < v.size(); i++){
	 		//j iterates over the array of interest

	 		//make upward polygon(convex hull)
	 		vector<float>st;

	 		st.push_back(i);
	 		st.push_back(i+1);

	 		for(Int j = i+2; j < i + threshold && j < v.size(); j++){

	 			while(st.size() >= 2){
	 				double slope1 = (double)(v[st[st.size()-1]][1] - v[st[st.size()-2]][1])/(st[st.size()-1] - st[st.size()-2]); 
            		double slope2 = (double)(v[st[st.size()-1]][1] - v[j][1])/(st[st.size()-1] - j);
            		//cout << slope2 << slope1 << endl;
            		if(slope1 <= slope2){
            			st.pop_back();
            		}else break;
	 			}
	 			st.push_back(j);
	 		}



	 		//make downward polygon(convex hull)
	 		vector<float>dt;

	 		dt.push_back(i);
	 		dt.push_back(i+1);

	 		for(Int j = i+2; j < i + threshold && j < v.size(); j++){

	 			while(dt.size() >= 2){
	 				double slope1 = (double)(v[dt[dt.size()-1]][2] - v[dt[dt.size()-2]][2])/(dt[dt.size()-1] - dt[dt.size()-2]); 
            		double slope2 = (double)(v[dt[dt.size()-1]][2] - v[j][2])/(dt[dt.size()-1] - j);
            		//cout << slope2 << slope1 << endl;
            		if(slope2 <= slope1){
            			dt.pop_back();
            		}else break;
	 			}
	 			dt.push_back(j);
	 		}

	 		// for(int k = 0; k < dt.size(); k ++ ){
	 		// 	cout << dt[k] << " " ;
	 		// }
	 		// cout << endl;

	 		//get maximum points on line for st and dt
	 		Int max_pts = 0;

	 		
	 		vector<vector<float>>slopes;
	 		float max_upper = 0.0;

	 		for(int q = 0; q < st.size(); q++){
	 			max_upper = max(max_upper, v[st[q]][1]);
	 		}

	 		float p1 = 0.0, p2=0.0, p3=0.0;
	 		int flag = 0;

	 		for(int a = 0; a < st.size() ; a ++){
	 			for(int b = a+1; b < st.size(); b++){
	 				for(int c = b+1; c < st.size(); c++){
	 					//I have 3 ranges 

	 					float l1 = 0.0 , h1 = 0.0, l2 = 0.0, h2 = 0.0, l3= 0.0, h3 = 0.0;
	 					l1 = max(v[st[a]][0], v[st[a]][3]);
	 					l2 = max(v[st[b]][0], v[st[b]][3]);
	 					l3 = max(v[st[c]][0], v[st[c]][3]);

	 					h1 = v[st[a]][1];
	 					h2 = v[st[b]][1];
	 					h3 = v[st[b]][1];

	 					if(abs(h1-max_upper) > 1e-5 && abs(h2-max_upper) > 1e-5, abs(h3-max_upper) > 1e-5 ) continue;

	 					float slope1 = (h3-h1)/(st[c]-st[a]);
	 					float slope2 = (l3-l1)/(st[c]-st[a]);

	 					float pt1 = h1 + (slope1) * (st[b] - st[a]);
	 					float pt2 = l1 + (slope2) * (st[b] - st[a]);

	 					if(pt1 > l2 && pt2 < h2){
	 						//is possible to make a line
	 						if(h2 <= pt1 && h2 >= pt2){
	 							float pt = h2;
	 							float ratio  = (pt1 - pt)/(pt - pt2);
	 							float fpt1 = (h1 + ratio*l1)/(1 + ratio);
	 							float fpt2 = (h3 + ratio*l3)/(1 + ratio);
	 							p1 = fpt1;
	 							p2 = pt;
	 							p3 = fpt2;
	 						}else{
	 							float pt = l2;
	 							float ratio  = (pt1 - pt)/(pt - pt2);
	 							float fpt1 = (h1 + ratio*l1)/(1 + ratio);
	 							float fpt2 = (h3 + ratio*l3)/(1 + ratio);
	 							p1 = fpt1;
	 							p2 = pt;
	 							p3 = fpt2;
	 						}
	 						//equation of line
	 						float slope = (p3-p1)/(st[c]-st[a]);
	 						//cout << slope << endl;
	 						if(st[c] - st[a] >= threshold-1) slopes.push_back({slope, st[a], p1, st[c], p2});

	 						flag = 1;
	 					}
	 					if(flag) break;
	 				}
	 				if(flag) break;
	 			}
	 			if(flag) break;
	 		}
			
			float min_lower = 999999999.0;
			for(int q = 0; q < dt.size(); q++){
	 			min_lower = min(min_lower, v[dt[q]][2]);
	 		}
	 		
	 		int flag2 = 0;
	 		for(int a = 0; a < dt.size() ; a ++){
	 			for(int b = a+1; b < dt.size(); b++){
	 				for(int c = dt.size()-1; c >b ; c--){
	 					//I have 3 ranges 

	 					float l1 = 0.0, h1 = 0.0, l2 = 0.0, h2 = 0.0, l3 = 0.0, h3 = 0.0;
	 					h1 = min(v[dt[a]][0], v[dt[a]][3]);
	 					h2 = min(v[dt[b]][0], v[dt[b]][3]);
	 					h3 = min(v[dt[c]][0], v[dt[c]][3]);

	 					l1 = v[dt[a]][2];
	 					l2 = v[dt[b]][2];
	 					l3 = v[dt[b]][2];

	 					if(abs(l1-min_lower) > 1e-5 && abs(l2-min_lower) > 1e-5, abs(l3-min_lower) > 1e-5 ) continue;

	 					float slope1 = (h3-h1)/(dt[c]-dt[a]);
	 					float slope2 = (l3-l1)/(dt[c]-dt[a]);

	 					float pt1 = h1 + (slope1) * (dt[b] - dt[a]);
	 					float pt2 = l1 + (slope2) * (dt[b] - dt[a]);

	 					if(pt1 > l2 && pt2 < h2){
	 						//is possible to make a line
	 						//draw a line parallel to line above formed 
	 						float pt = 0.0;
	 						if(h2 <= pt1 && h2 >= pt2){
	 							pt = h2;
	 						}else{
	 							pt = l2;
	 						}

	 						for(int s = 0; s < slopes.size(); s++){
	 							//if 
	 							float y1 = pt + slopes[s][0] * (dt[a] - dt[b]);
	 							float y2 = pt + slopes[s][0] * (dt[c] - dt[b]);

	 							if((y1 <= h1 && y1 >=l1)&&(y2 <= h3 && y2 >= l3)){
	 								//possible
	 								//dt[a], y1 and dt[c], y2
	 								//cout << "success" << endl;
	 								if(dt[c] - dt[a] >= threshold-1){
	 								 	//cout << y1 << " " << y2 <<  endl;
	 								
	 									flag2 = 1;
	 									final_ans.push_back({slopes[s][1], slopes[s][2], slopes[s][3], slopes[s][4]});
	 									final_ans.push_back({dt[a], y1, dt[c], y2});
	 									i+=threshold-1;
	 									break; 
	 								}
	 								
	 							}
	 							
	 						}
	 						
	 					}
	 					if(flag2) break;
	 				}
	 				if(flag2) break;
	 			}
	 			if(flag2) break;
	 		}

	 		//
	 	}
	
	 	for(int i = 0; i < final_ans.size(); i++){
	 		cout << content[final_ans[i][0] + 1][0] << " " <<final_ans[i][1] << " " <<content[final_ans[i][2]+1][0] << " " <<final_ans[i][3] <<endl;
	 	}
	 	//fclose();
	}
	return 0;
}