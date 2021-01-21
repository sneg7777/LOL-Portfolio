#pragma once



namespace PKH
{
	enum class PathFinderType
	{
		None,
		Dijkstra,
		Astar,
	};


	class PathFinder
	{
	public:
		struct Node
		{
		public:
			Node* parent;
			Vector3 position;
			vector<Node*> adjacency;
			Node* destination;

			Node();
			Node(PathFinder::Node* parent, Vector3 position);
			virtual ~Node();

			virtual int G();
			virtual int H(Node* dest);
			virtual int F(Node* dest);

		};

		PathFinder();
		virtual ~PathFinder();

		virtual bool Search(const Vector3& start, const Vector3& dest) PURE;
		
	protected:
		// Search ���� ����� �� �͵� (�Ź�)
		PKH::PathFinder::Node* FindStartNode(const Vector3& startPos, float radius = INFINITY);
		PKH::PathFinder::Node* FindDestinationNode(const Vector3& destPos, float radius = INFINITY);
		void SetDestination(PathFinder::Node* dest);
		// Ž�� �Ϸ�� ��� ����Ʈ�� ����
		void SetPath();
		// ��� Ž�� �Ϸ�� ����߿� ���۳�� �ĺ��� �ִ��� üũ
		void OptimizeStartNode();
		void OptimizeDestinationNode(const Vector3& destPos);
		void Optimize();
	public:
		// �ܺο��� ���� ���ٰ� (�ѹ���)
		void AddNode(DWORD index, PathFinder::Node* pNode);
		void LinkNode(DWORD srcIndex, DWORD destIndex);

	public:
		// getter setter
		PathFinderType GetType();

		// ��ã�Ⱑ ������ ���
		// resultNode �� destNode �̰�
		// resultNode �� parent�� Ÿ�� Ÿ�� ���ٺ��� ������� ����
		// ����Ǿ��ִ� ��� ���� �����.
		// p.s ����� true�ε� resultNode�� parent�� nullptr�̸� �̹� �������ΰ�
		PKH::PathFinder::Node* GetResultNode();
		list<PKH::PathFinder::Node*>* GetPath();
		
	protected:
		// ���
		map<int, PKH::PathFinder::Node*> nodes;
		PathFinderType type = PathFinderType::None;
		PKH::PathFinder::Node* resultNode = nullptr;
		list<PathFinder::Node*> path;

		// ���۳�� �ĺ�
		// ���۳�� Ž���� ���� ����� ��带 ����������
		// �� ��尡 ������ ���� �ƴ� ���� ����.
		// ������ ���۳�� �ĺ��ڵ��� �־����
		// ���� ��ο��� �������� ���۳���� �ĺ��� �ִٸ�
		// �� �ĺ� ��带 ���۳��� �����ؾ���.
		// key = dist ( �Ÿ��� ���� ���� )  
		map<int, Node*> candidatesStart;
		map<int, Node*> candidatesDest;
	};


}