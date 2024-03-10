#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define MAX 1
#define MIN -1 

using namespace std;

struct heap_node {
	int id; // 第幾個加進vector的資料 
	int student_count; // 學生數 
};

// build the Min heap
void MinHeapRe(vector<heap_node>& minHeap, int data_num) {
    if (data_num <= 1) {
        return; // 終止遞迴
    }

    if (minHeap[data_num - 1].student_count < minHeap[(data_num / 2) - 1].student_count) {
        // 進行交換
        heap_node temp = minHeap[data_num - 1];
        minHeap[data_num - 1] = minHeap[(data_num / 2) - 1];
        minHeap[(data_num / 2) - 1] = temp;

        // 順勢往上檢查是否要再交換
        MinHeapRe(minHeap, data_num / 2); // 遞迴呼叫
    }
}

bool MinMaxHeap_father(vector<heap_node>& min_max_heap, int data_num, int type) {
	
	if (data_num <= 1) {
        return false; // 根節點 
    }
	
	// 有沒有跟父節點交換過 
	bool changed = false;
	
	// 先檢查父節點需不需要交換
	if (type == MIN) {
	
		if (min_max_heap[data_num - 1].student_count < min_max_heap[(data_num / 2) - 1].student_count) {
        	// 進行交換
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 2) - 1];
        	min_max_heap[(data_num / 2) - 1] = temp;

        	// 不需要遞迴呼叫
       		
       		changed = true;
   		}
				
	}
		
	if (type == MAX) {
		
		if (min_max_heap[data_num - 1].student_count > min_max_heap[(data_num / 2) - 1].student_count) {
    		// 進行交換
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 2) - 1];
        	min_max_heap[(data_num / 2) - 1] = temp;

        	// 不需要遞迴呼叫
        	
        	changed = true;
    	}
	}
	
	return changed;	
}

void MinMaxHeapRe(vector<heap_node>& min_max_heap, int data_num, int type) {
		
	// 以下開始min max排序
	// 且會開始遞迴呼叫
	
	if (data_num < 4) {
        return; // 終止遞迴
    }

	if (type == MIN) {

		// Min Heap的情況，如果目前節點比祖父節點要小，則交換 
    	if (min_max_heap[data_num - 1].student_count < min_max_heap[(data_num / 4) - 1].student_count) {
        	// 進行交換
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 4) - 1];
        	min_max_heap[(data_num / 4) - 1] = temp;

        	// 順勢往上檢查是否要再交換
        	MinMaxHeapRe(min_max_heap, data_num / 4, type); // 遞迴呼叫
    	}
	}
    
    else if (type == MAX) {

    	// Max Heap的情況，如果目前節點比祖父節點要大，則交換 
		if (min_max_heap[data_num - 1].student_count > min_max_heap[(data_num / 4) - 1].student_count) {
        	// 進行交換
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 4) - 1];
        	min_max_heap[(data_num / 4) - 1] = temp;

        	// 順勢往上檢查是否要再交換
       		MinMaxHeapRe(min_max_heap, data_num / 4, type); // 遞迴呼叫
    	}
		
	}
}

void MinHeap(string fileName) {
    int data_num = 0; 
    int count = 0;
    string garbage;
    // data_num是序號, count是學生數，之後會用其值進行排序，garbage是因為資料特性，而被捨棄的資料 
    
    // 用vector陣列儲存heap_node資料類別，cur_heap_node是infile的對象 ，在infile之後再將資料帶入vector 
    heap_node cur_heap_node;
    std::string line;
    
    std::ifstream infile(fileName);
    
    // 資料開啟失敗 
    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line);
    
    std::vector<heap_node> student_count;
    
    int tokenCount = 0;
    
    while (infile >> garbage) {
    	// 讀過把前面不需要的 
        tokenCount++;
        
        if (tokenCount == 8) {
        	infile >> count;
        	data_num = data_num + 1;
        	
			// 需要的資料
			cur_heap_node.id = data_num;			
            cur_heap_node.student_count = count;
        	
            student_count.push_back(cur_heap_node);
            MinHeapRe( student_count, cur_heap_node.id );
            
            // 讀到要的資料後跳過剩下的 
            std::getline(infile, line);
            tokenCount = 0; // 下一行重新開始 
        }
    }

    infile.close();
    
    // 確認資料都有放到vector
    /* 
    for (int i = 0; i < student_count.size(); i++) {
    	cout << student_count[i].id << " ";
        cout << student_count[i].student_count << endl;
    }
    */
	
	// 印出root, bottom, leftmost bottom
	cout << "<min heap>" << endl;
	cout << "root: " << "[" << student_count[0].id << "] " << student_count[0].student_count << endl;
	cout << "bottom: " << "[" << student_count[(student_count.size() - 1)].id << "] " << student_count[(student_count.size() - 1)].student_count << endl;
	
	// 找出leftmost bottom
	int node_num = 1;
	while (node_num < student_count.size()) {
		node_num = node_num * 2;
	}
	// 迴圈過後，node_num = 大於vector size的最小2次方數
	// 該數先'除於2，再減一(因為vector從0開始)即可得leftmost bottom在vector裡的位置
	node_num = node_num / 2;
	 
	cout << "leftmost bottom: " << "[" << student_count[(node_num)-1].id << "] " << student_count[(node_num)-1].student_count << endl;
	 
}

void Min_Max_Heap(string fileName) {
    int data_num = 0; 
    int count = 0;
    string garbage;
    int type = MIN;
    // data_num是序號, count是學生數，之後會用其值進行排序，garbage是因為資料特性，而被捨棄的資料，type是目前的heap種類，初始(第一層)是min heap 
    
    // 用vector陣列儲存heap_node資料類別，cur_heap_node是infile的對象 ，在infile之後再將資料帶入vector 
    heap_node cur_heap_node;
    std::string line;
    
    std::ifstream infile(fileName);
    
    // 資料開啟失敗 
    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line);
    
    std::vector<heap_node> student_count;
    
    int tokenCount = 0;
    
    while (infile >> garbage) {
    	// 讀過把前面不需要的 
        tokenCount++;
        
        if (tokenCount == 8) {
        	infile >> count;
        	data_num = data_num + 1;
        	
			// 需要的資料
			cur_heap_node.id = data_num;			
            cur_heap_node.student_count = count;
        	
            student_count.push_back(cur_heap_node);
            
            // 半段目前的節點處在min heap的部分還是max heap 
            int depth = 0;
            int temp = 1;
            while (temp < student_count.size()) {
            	depth++;
            	temp = temp * 2;
			}
            
            // 奇數層是min，偶數層次max
			if (depth % 2 == 0) {
				type = MAX;
			} 
			else {
				type = MIN;
			}
            
            // 讀到要的資料後跳過剩下的 
            std::getline(infile, line);
            
            // 些許條件的初始化 
            tokenCount = 0;
            type = MIN;
            
            // 檢查需不需要跟父節點交換
			bool changed = MinMaxHeap_father(student_count, data_num, type * -1);
			
			// 如果有跟父節點交換，檢查的節點編號跟heap type要更新
			int data_num_temp = data_num;
			if (changed) {
				data_num_temp = data_num_temp / 2;
				type = type * -1;
			} 
            
            // 往上進行跟祖父節點的交換
			MinMaxHeapRe(student_count, data_num_temp, type);
			
			// 讀到要的資料後跳過剩下的 
            std::getline(infile, line);
            
            // 些許條件的初始化 
            tokenCount = 0;
                        
            // 下一行重新開始
			
			cout << "test root: " << "[" << student_count[0].id << "] " << student_count[0].student_count << endl;
        }
    }

    infile.close();
    
	// 印出root, bottom, leftmost bottom
	cout << "<min-max heap>" << endl;
	cout << "root: " << "[" << student_count[0].id << "] " << student_count[0].student_count << endl;
	cout << "bottom: " << "[" << student_count[(student_count.size() - 1)].id << "] " << student_count[(student_count.size() - 1)].student_count << endl;
	
	// 找出leftmost bottom
	int node_num = 1;
	while (node_num < student_count.size()) {
		node_num = node_num * 2;
	}
	// 迴圈過後，node_num = 大於vector size的最小2次方數
	// 該數先'除於2，再減一(因為vector從0開始)即可得leftmost bottom在vector裡的位置
	node_num = node_num / 2;
	 
	cout << "leftmost bottom: " << "[" << student_count[(node_num)-1].id << "] " << student_count[(node_num)-1].student_count << endl;
	 
}

int main() {
	
	int command = 0;
    
    do {
    	cout << endl;
		cout << "********** Heap Construction **********" << endl;
		cout << "* 0. QUIT                             *" << endl;
		cout << "* 1. Build a min heap                 *" << endl;
		cout << "* 2. Build a min-max heap             *" << endl;
		cout << "***************************************" << endl;
    
    	cout << "Input a choice(0, 1, 2):";
    	
    	cin >> command;
    	cout << endl;
    
    	std::string fileName;
    	if (command == 1) {
    		cout << "Input a file number ([0] Quit):";

    		// 從使用者輸入中讀取檔案編號
    		cin >> fileName;
    		// 組合檔案名稱	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		MinHeap(fileName);
		}
		
		if (command == 2) {
			cout << "Input a file number ([0] Quit):";
			
			// 從使用者輸入中讀取檔案編號
    		cin >> fileName;
    		// 組合檔案名稱	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		Min_Max_Heap(fileName);
		}
	
		if (command == 0) {
			break;
		}
	} while (command != 0);

	return 0;
}
