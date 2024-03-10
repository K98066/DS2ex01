#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define MAX 1
#define MIN -1 

using namespace std;

struct heap_node {
	int id; // �ĴX�ӥ[�ivector����� 
	int student_count; // �ǥͼ� 
};

// build the Min heap
void MinHeapRe(vector<heap_node>& minHeap, int data_num) {
    if (data_num <= 1) {
        return; // �פ�j
    }

    if (minHeap[data_num - 1].student_count < minHeap[(data_num / 2) - 1].student_count) {
        // �i��洫
        heap_node temp = minHeap[data_num - 1];
        minHeap[data_num - 1] = minHeap[(data_num / 2) - 1];
        minHeap[(data_num / 2) - 1] = temp;

        // ���թ��W�ˬd�O�_�n�A�洫
        MinHeapRe(minHeap, data_num / 2); // ���j�I�s
    }
}

bool MinMaxHeap_father(vector<heap_node>& min_max_heap, int data_num, int type) {
	
	if (data_num <= 1) {
        return false; // �ڸ`�I 
    }
	
	// ���S������`�I�洫�L 
	bool changed = false;
	
	// ���ˬd���`�I�ݤ��ݭn�洫
	if (type == MIN) {
	
		if (min_max_heap[data_num - 1].student_count < min_max_heap[(data_num / 2) - 1].student_count) {
        	// �i��洫
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 2) - 1];
        	min_max_heap[(data_num / 2) - 1] = temp;

        	// ���ݭn���j�I�s
       		
       		changed = true;
   		}
				
	}
		
	if (type == MAX) {
		
		if (min_max_heap[data_num - 1].student_count > min_max_heap[(data_num / 2) - 1].student_count) {
    		// �i��洫
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 2) - 1];
        	min_max_heap[(data_num / 2) - 1] = temp;

        	// ���ݭn���j�I�s
        	
        	changed = true;
    	}
	}
	
	return changed;	
}

void MinMaxHeapRe(vector<heap_node>& min_max_heap, int data_num, int type) {
		
	// �H�U�}�lmin max�Ƨ�
	// �B�|�}�l���j�I�s
	
	if (data_num < 4) {
        return; // �פ�j
    }

	if (type == MIN) {

		// Min Heap�����p�A�p�G�ثe�`�I�񯪤��`�I�n�p�A�h�洫 
    	if (min_max_heap[data_num - 1].student_count < min_max_heap[(data_num / 4) - 1].student_count) {
        	// �i��洫
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 4) - 1];
        	min_max_heap[(data_num / 4) - 1] = temp;

        	// ���թ��W�ˬd�O�_�n�A�洫
        	MinMaxHeapRe(min_max_heap, data_num / 4, type); // ���j�I�s
    	}
	}
    
    else if (type == MAX) {

    	// Max Heap�����p�A�p�G�ثe�`�I�񯪤��`�I�n�j�A�h�洫 
		if (min_max_heap[data_num - 1].student_count > min_max_heap[(data_num / 4) - 1].student_count) {
        	// �i��洫
        	heap_node temp = min_max_heap[data_num - 1];
        	min_max_heap[data_num - 1] = min_max_heap[(data_num / 4) - 1];
        	min_max_heap[(data_num / 4) - 1] = temp;

        	// ���թ��W�ˬd�O�_�n�A�洫
       		MinMaxHeapRe(min_max_heap, data_num / 4, type); // ���j�I�s
    	}
		
	}
}

void MinHeap(string fileName) {
    int data_num = 0; 
    int count = 0;
    string garbage;
    // data_num�O�Ǹ�, count�O�ǥͼơA����|�Ψ�ȶi��ƧǡAgarbage�O�]����ƯS�ʡA�ӳQ�˱󪺸�� 
    
    // ��vector�}�C�x�sheap_node������O�Acur_heap_node�Oinfile����H �A�binfile����A�N��Ʊa�Jvector 
    heap_node cur_heap_node;
    std::string line;
    
    std::ifstream infile(fileName);
    
    // ��ƶ}�ҥ��� 
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
    	// Ū�L��e�����ݭn�� 
        tokenCount++;
        
        if (tokenCount == 8) {
        	infile >> count;
        	data_num = data_num + 1;
        	
			// �ݭn�����
			cur_heap_node.id = data_num;			
            cur_heap_node.student_count = count;
        	
            student_count.push_back(cur_heap_node);
            MinHeapRe( student_count, cur_heap_node.id );
            
            // Ū��n����ƫ���L�ѤU�� 
            std::getline(infile, line);
            tokenCount = 0; // �U�@�歫�s�}�l 
        }
    }

    infile.close();
    
    // �T�{��Ƴ������vector
    /* 
    for (int i = 0; i < student_count.size(); i++) {
    	cout << student_count[i].id << " ";
        cout << student_count[i].student_count << endl;
    }
    */
	
	// �L�Xroot, bottom, leftmost bottom
	cout << "<min heap>" << endl;
	cout << "root: " << "[" << student_count[0].id << "] " << student_count[0].student_count << endl;
	cout << "bottom: " << "[" << student_count[(student_count.size() - 1)].id << "] " << student_count[(student_count.size() - 1)].student_count << endl;
	
	// ��Xleftmost bottom
	int node_num = 1;
	while (node_num < student_count.size()) {
		node_num = node_num * 2;
	}
	// �j��L��Anode_num = �j��vector size���̤p2�����
	// �Ӽƥ�'����2�A�A��@(�]��vector�q0�}�l)�Y�i�oleftmost bottom�bvector�̪���m
	node_num = node_num / 2;
	 
	cout << "leftmost bottom: " << "[" << student_count[(node_num)-1].id << "] " << student_count[(node_num)-1].student_count << endl;
	 
}

void Min_Max_Heap(string fileName) {
    int data_num = 0; 
    int count = 0;
    string garbage;
    int type = MIN;
    // data_num�O�Ǹ�, count�O�ǥͼơA����|�Ψ�ȶi��ƧǡAgarbage�O�]����ƯS�ʡA�ӳQ�˱󪺸�ơAtype�O�ثe��heap�����A��l(�Ĥ@�h)�Omin heap 
    
    // ��vector�}�C�x�sheap_node������O�Acur_heap_node�Oinfile����H �A�binfile����A�N��Ʊa�Jvector 
    heap_node cur_heap_node;
    std::string line;
    
    std::ifstream infile(fileName);
    
    // ��ƶ}�ҥ��� 
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
    	// Ū�L��e�����ݭn�� 
        tokenCount++;
        
        if (tokenCount == 8) {
        	infile >> count;
        	data_num = data_num + 1;
        	
			// �ݭn�����
			cur_heap_node.id = data_num;			
            cur_heap_node.student_count = count;
        	
            student_count.push_back(cur_heap_node);
            
            // �b�q�ثe���`�I�B�bmin heap�������٬Omax heap 
            int depth = 0;
            int temp = 1;
            while (temp < student_count.size()) {
            	depth++;
            	temp = temp * 2;
			}
            
            // �_�Ƽh�Omin�A���Ƽh��max
			if (depth % 2 == 0) {
				type = MAX;
			} 
			else {
				type = MIN;
			}
            
            // Ū��n����ƫ���L�ѤU�� 
            std::getline(infile, line);
            
            // �ǳ\���󪺪�l�� 
            tokenCount = 0;
            type = MIN;
            
            // �ˬd�ݤ��ݭn����`�I�洫
			bool changed = MinMaxHeap_father(student_count, data_num, type * -1);
			
			// �p�G������`�I�洫�A�ˬd���`�I�s����heap type�n��s
			int data_num_temp = data_num;
			if (changed) {
				data_num_temp = data_num_temp / 2;
				type = type * -1;
			} 
            
            // ���W�i��򯪤��`�I���洫
			MinMaxHeapRe(student_count, data_num_temp, type);
			
			// Ū��n����ƫ���L�ѤU�� 
            std::getline(infile, line);
            
            // �ǳ\���󪺪�l�� 
            tokenCount = 0;
                        
            // �U�@�歫�s�}�l
			
			cout << "test root: " << "[" << student_count[0].id << "] " << student_count[0].student_count << endl;
        }
    }

    infile.close();
    
	// �L�Xroot, bottom, leftmost bottom
	cout << "<min-max heap>" << endl;
	cout << "root: " << "[" << student_count[0].id << "] " << student_count[0].student_count << endl;
	cout << "bottom: " << "[" << student_count[(student_count.size() - 1)].id << "] " << student_count[(student_count.size() - 1)].student_count << endl;
	
	// ��Xleftmost bottom
	int node_num = 1;
	while (node_num < student_count.size()) {
		node_num = node_num * 2;
	}
	// �j��L��Anode_num = �j��vector size���̤p2�����
	// �Ӽƥ�'����2�A�A��@(�]��vector�q0�}�l)�Y�i�oleftmost bottom�bvector�̪���m
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

    		// �q�ϥΪ̿�J��Ū���ɮ׽s��
    		cin >> fileName;
    		// �զX�ɮצW��	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		MinHeap(fileName);
		}
		
		if (command == 2) {
			cout << "Input a file number ([0] Quit):";
			
			// �q�ϥΪ̿�J��Ū���ɮ׽s��
    		cin >> fileName;
    		// �զX�ɮצW��	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		Min_Max_Heap(fileName);
		}
	
		if (command == 0) {
			break;
		}
	} while (command != 0);

	return 0;
}
