#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "InputFile.h"



// Identificador del manager al que vamos a asociar todos los VBOs
GLuint vao;

// Identifcador del manager de los shaders (shaderProgram)
GLuint shaderProgram;

void Initialize()
{
	// Creando toda la memoria que el programa va a utilizar.

	// Creaci�n del atributo de posiciones de los v�rtices.
	// Lista de vec2
	
		//CIRCULO- TRIANGLES_FAN
		/*std::vector<glm::vec2> positions;

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
		}*/

		// Claramente en el CPU y RAM
	std::vector<glm::vec2> positions;
	positions.push_back(glm::vec2(0.3f, -0.4f));
	positions.push_back(glm::vec2(0.6f, -0.8f));
	positions.push_back(glm::vec2(0.5f, 0.1f));
	positions.push_back(glm::vec2(0.9f, 0.3f));
	positions.push_back(glm::vec2(0.0f, 0.5f));
	positions.push_back(glm::vec2(0.0f, 0.9f));
	positions.push_back(glm::vec2(-0.5f, 0.1f));
	positions.push_back(glm::vec2(-0.9f, 0.3f));
	positions.push_back(glm::vec2(-0.3f, -0.4f));
	positions.push_back(glm::vec2(-0.6f, -0.8f));
	positions.push_back(glm::vec2(0.3f, -0.4f));
	positions.push_back(glm::vec2(0.6f, -0.8f));
	
	

	// Arreglo de colores en el cpu
	std::vector<glm::vec3> colors;
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	// Queremos generar 1 manager
	glGenVertexArrays(1, &vao);
	// Utilizar el vao. A partir de este momento, todos VBOs creados y configurados
	// se van a asociar a este manager.
	glBindVertexArray(vao);

	// Identificador del VBO de posiciones.
	GLuint positionsVBO;
	// Creaci�n del VBO de posiciones
	glGenBuffers(1, &positionsVBO);
	// Activamos el buffer de posiciones para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * positions.size(),
		positions.data(), GL_STATIC_DRAW);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(0);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este VBO en este momento.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(),
		colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desactivamos el manager
	glBindVertexArray(0);

	// Creamos un objeto para leer archivos de texto
	InputFile ifile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde est�
	// el c�digo del vertex shader.
	ifile.Read("DiscardCenter.vert");
	// Obtenemos el c�digo fuente y lo guardamos
	// en un string
	std::string vertexSource = ifile.GetContents();
	// Creamos un shader de tipo vertex
	// guardamos su identificador en una variable.
	GLuint vertexShaderHandle =
		glCreateShader(GL_VERTEX_SHADER);
	// Obtener los datos en el formato correcto
	const GLchar *vertexSource_c =
		(const GLchar*)vertexSource.c_str();
	// Le estamos dando el c�digo fuente a OpenGL
	// para que se lo asigne al shader
	glShaderSource(vertexShaderHandle, 1,
		&vertexSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ning�n error.
	glCompileShader(vertexShaderHandle);

	ifile.Read("DiscardCenter.frag");
	std::string fragmentSource = ifile.GetContents();
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);

	// Creamos el identificador para el manager de los shaders
	shaderProgram = glCreateProgram();
	// Adjuntamos el vertex shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, vertexShaderHandle);
	// Adjuntamos el fragment shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, fragmentShaderHandle);
	// Asociamos un buffer con indice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	// Asociamos un buffer con indice 1 (colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	// Ejecutamos el proceso de linker (asegurarnos que el vertex y fragment son
	// compatibles)
	glLinkProgram(shaderProgram);
}

void GameLoop()
{
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activamos el vertex shader y el fragment shader utilizando el manager
	glUseProgram(shaderProgram);
	// Activamos el manager, en este momento se activan todos los
	// VBOs asociados autom�ticamente.
	glBindVertexArray(vao);
	// Funci�n de dibujado sin indices.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);
	// Terminamos de utilizar el manager
	glBindVertexArray(0);
	// Desactivamos el manager
	glUseProgram(0);

	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();
}

void Idle()
{
	// Cuando OpenGL entra en modo de reposo 
	// (para guardar bateria, por ejemplo)
	// le decimos que vuelva a dibujar ->
	// Vuelve a mandar a llamar GameLoop
	glutPostRedisplay();
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
	// Inicializar freeglut
	// Freeglut se encarga de crear una ventana
	// en donde podemos dibujar
	glutInit(&argc, argv);
	// Solicitando una versi�n espec�fica de OpenGL.
	glutInitContextVersion(4, 4);
	// Iniciar el contexto de OpenGL. El contexto se refiere
	// a las capacidades que va a tener nuestra aplicaci�n
	// gr�fica.
	// En este caso estamos trabajando con el pipeline programable.
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la ventana.
	// Un evento que nos interesa es cuando alguien cierra la ventana.
	// En este caso, simplemente dejamos de renderear la esscena y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando un buffer
	// true color RGBA, un buffer de profundidad y un segundo buffer para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);
	// Creamos la ventana y le damos un t�tulo.
	glutCreateWindow("Hello World GL");
	// Asociamos una funci�n de render.
	//Esta funci�n se mandar� a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);
	// Asociamos una funci�n para el cambio de resoluci�n
	// de la ventana. Freeglut la va a mandar a llamar
	// cuando alguien cambie el tama�o de la venta.
	glutReshapeFunc(ReshapeWindow);
	// Asociamos la funci�n que se mandar� a llamar
	// cuando OpenGL entre en modo de reposo.
	glutIdleFunc(Idle);

	// Inicializar GLEW. Esta librer�a se encarga de obtener el API de OpenGL de
	// nuestra tarjeta de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configurar OpenGL. Este es el color por default del buffer de color
	// en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	// Ademas de solicitar el buffer de profundidad, tenemos
	// que decirle a OpenGL que lo queremos activo
	glEnable(GL_DEPTH_TEST);
	// Activamos el borrado de caras traseras.
	// Ahora todos los triangulos que dibujemos deben estar en CCW
	glEnable(GL_CULL_FACE);
	// No dibujar las caras traseras de las geometr�as.
	glCullFace(GL_BACK);

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Configuraci�n inicial de nuestro programa.
	Initialize();

	// Iniciar la aplicaci�n. El main se pausar� en esta l�nea hasta que se cierre
	// la venta de OpenGL.
	glutMainLoop();

	return 0;
}