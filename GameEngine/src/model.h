class Model {

private:
	float* vertices = nullptr;
	unsigned int vao {}, vbo {};
	unsigned int programId {};
	unsigned int size;
	unsigned int attribSize;

public:
	void draw();
	void create(float vertices[], unsigned int size, unsigned int attribSize);
};