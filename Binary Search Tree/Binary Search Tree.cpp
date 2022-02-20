#include <vector>
#include <utility>
#include <string>
#include <queue> 
#include <iostream>


using namespace std; 

struct Person
{
	int mId; 
	string mName; 

	explicit Person(int id, string name) : mId(id), mName(move(name))
	{
	}
};

struct Node
{
	Person mData;  
	Node* mLeft;
	Node* mRight;

	explicit Node(Person data) : mData(move(data)), mLeft(nullptr), mRight(nullptr)
	{}
};

struct BST
{
	Node* mFirst; 

	BST() : mFirst(nullptr)
	{
	}

	/**
	 * \brief Average Complexity: lg(n) 
	 * \param person 
	 */
	void insert(const Person& person)
	{
		Node* newNode = new Node(person);

		if (mFirst == nullptr) // The BST was empty 
		{
			mFirst = newNode; 
			return; 
		}

		Node* currentNode = mFirst; 

		while (true)
		{
			if (person.mId < currentNode->mData.mId)
			{
				if (currentNode->mLeft == nullptr) // We have reached a leaf node 
				{
					currentNode->mLeft = newNode;
					break; 
				}
				currentNode = currentNode->mLeft;
			}
			else
			{
				if (currentNode->mRight == nullptr) // We have reached a leaf node 
				{
					currentNode->mRight = newNode;
					break; 
				}
				currentNode = currentNode->mRight; 
			}
		}
	}
};

/**
 * \brief Can be used for Tree Sort
 * \param node 
 * \return 
 */
vector<Person> in_order(Node* node)
{
	vector<Person> output;

	if (node == nullptr) return output; 

	const vector<Person> leftResult = in_order(node->mLeft);
	vector<Person> rightResult = in_order(node->mRight); 

	output.insert(output.end(), leftResult.begin(), leftResult.end());
	output.push_back(node->mData);
	output.insert(output.end(), rightResult.begin(), rightResult.end());

	return output; 
}

/**
 * \brief Unlike the other, does not waste resources through unnecessary copies 
 * \param node 
 * \param result 
 */
void in_order_faster(Node* node, vector<Person>& result)
{
	if (node == nullptr) return;

	in_order_faster(node->mLeft, result);
	result.push_back(node->mData);
	in_order_faster(node->mRight, result); 
}

void post_order_faster(Node* node, vector<Person>& result)
{
	if (node == nullptr) return;

	in_order_faster(node->mLeft, result);
	in_order_faster(node->mRight, result); 
	result.push_back(node->mData);
}

void pre_order_faster(Node* node, vector<Person>& result)
{
	if (node == nullptr) return;

	result.push_back(node->mData);
	in_order_faster(node->mLeft, result);
	in_order_faster(node->mRight, result); 
}

vector<Person> bfs(Node* node)
{
	vector<Person> output;

	queue<Node*> queue;
	queue.push(node); 

	while(!queue.empty())
	{
		Node* next = queue.front();
		queue.pop();

		if (next != nullptr)
		{
			output.push_back(next->mData);

			queue.push(next->mLeft);
			queue.push(next->mRight); 
		}
	}

	return output; 
}

int main()
{


}

