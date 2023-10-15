class Parser {
	public:
	Parser(vector<Token>& tokens);
	void parse();
	void print();
	void error(string msg);
	private:
	TreeNode* program();
	TreeNode* statement();
	TreeNode* label();
	TreeNode* instruction();
	TreeNode* operand();
	TreeNode* register_operand();
	TreeNode* identifier_operand();
	TreeNode* number_operand();
	private:
	vector<Token>& tokens_;
	int pos_;
	TreeNode* root_;
	};
	