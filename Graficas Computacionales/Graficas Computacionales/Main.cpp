
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "InputFile.h"


GLuint vao; //Identificador del manage al que vamos a asociar todos los VBOs

GLuint shaderProgram; //Identificador del manager de los shaders (shaderProgram)

void Initialize()
{
	std::vector<glm::vec2> positions;

	std::vector<glm::vec3> colors;

	float r = 1.0;
	float X = 1.0;
	float Y = 0.0;
	float contador = 0.0f;

	positions.push_back(glm::vec2(0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	while (contador <= 360.0f) {

		float angulo = glm::radians(contador);
		float x = r*(glm::cos(angulo));
		float y = r*(glm::sin(angulo));

		positions.push_back(glm::vec2(x, y));
		colors.push_back(glm::vec3(x, y, 0.0f));


		contador = contador + 1.0f;



	}


	//Crear una nueva lista. Un color por cada vértice, en este caso 4











	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint positionsVBO; //Entero sin signo
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO); //activar el buffer de posiciones para poder utilizarlo
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * positions.size(), positions.data(), GL_STATIC_DRAW); //Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);//configuramos los datos del atributo en la tarjeta de video
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	InputFile ifile;     //Creamos un objeto para leer archivo

	ifile.Read("DiscardCenter.vert"); //VERTEX SHADER. Leemos el archivo default.vert donde está el codigo del vertex shader
	std::string vertexSource = ifile.GetContents(); //Obtenemos el código fuente y lo guardamos en un string
	GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER); //Creamos un shader de tipo vertex y guardamos su identificador en una variable
	const GLchar*vertexSource_c = (const GLchar*)vertexSource.c_str(); //Obtener los datos en el formato correcto, en este caso en el lenguaje C
	glShaderSource(vertexShaderHandle, 1, &vertexSource_c, nullptr);
	glCompileShader(vertexShaderHandle); //Compilamos el shader en busca de errores


	ifile.Read("DiscardCenter.frag");
	std::string fragmentSource = ifile.GetContents();
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);


	shaderProgram = glCreateProgram(); //Creamos el identificador para el manager de los shaders
	glAttachShader(shaderProgram, vertexShaderHandle); //Adjuntamos el vertex shader al manager
	glAttachShader(shaderProgram, fragmentShaderHandle); //Adjuntamos el fragment shader al manager
	glBindAttribLocation(shaderProgram, 0, "VertexPosition"); //Asociamos un buffer con índice 0(posiciones) a la variable vertexPosition
	glBindAttribLocation(shaderProgram, 1, "VertexColor"); //Asociamos un buffer con índice 1(colores) a la variable vertexColor
	glLinkProgram(shaderProgram); // Aseguramos que el vertex y fragment son compatibles por medio del proceso de linker

}

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpiamos el buffer de control y el de profundidad. Siempre hacerlo al inicio del frame

	glUseProgram(shaderProgram); //Activamos el vertex shader y el fragment shaderl utilizando el manager

	glBindVertexArray(vao); //activamos el mamager y con esto se activan todos los VBOs asociados automaticamente
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362); //funcion de dibujando sin indices
	glBindVertexArray(0); //terminamos de utilizar el manager

	glUseProgram(0);

	//cuando terminamos de renderear cambiamos los buffers
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitContextVersion(4, 5);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello World GL");
	glutDisplayFunc(GameLoop);
	glewInit();

	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);// la venta de OpenGL.
	std::cout << glGetString(GL_VERSION) << std::endl;
	Initialize();
	glutMainLoop();

	return 0;
}
