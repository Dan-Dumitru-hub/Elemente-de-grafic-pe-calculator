#include "Laborator6.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include <Laboratoare\Laborator6\Camera.h>



using namespace std;
float sx=0, sy=5,sz=0;//pozitia sferei
float ty=0.1;//indicator care are rol de gravitatie pt sfera

float c1y=1, c1z=0;//pozitia initiala pt inceputul setului 1 de platforme
float c2y = 1, c2z = 21; // pozitia initiala pt inceputul setului 2 de platforme


int speed=5;//viteza cu care se misca platformele
int fuel = 1000;

int cameratype=1;
int atins=0;// indicator care imi zice daca sfera a atins o platforma

int time=100;

int random[5],random2[5];//vector care il schimb atunci cand trebuie sa plasez alte platforme

glm::mat4 modelsphere = glm::mat4(1);

int posx[5];//vector de pozitii pentru platforme

int v[5],w[5];



int endgame = 0;
int blocked = 0;

Laborator6::Laborator6()
{
}

Laborator6::~Laborator6()
{
}

void Laborator6::Init(){
	//initializez pozitiile platformelor astfel incat sfera sa se miste stanga si dreapta pe ele
	posx[0] = -4;
	posx[1] = -2;
	posx[2] = 0;
	posx[3] = 2;
	posx[4] = 4;

	for (int i = 0;i < 5;i++) {
		random[i] = rand() / 30 % 5;
		random2[i] = rand() / 30 % 5;
	}

	projectionMatrix=glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	camera = new Laborator::Camera1();

	camera->Set(glm::vec3(0, 5, -3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-1, 1,  1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-1, -1,  -1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(1, -1,  -1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-1, 1,  -1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1, 0, 1))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("purplecube", vertices, indices);
	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-1, 1,  1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-1, -1,  -1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1, -1,  -1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-1, 1,  -1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(0, 0, 1))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("bluecube", vertices, indices);
	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-1, 1,  1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-1, -1,  -1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1, -1,  -1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-1, 1,  -1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("redcube", vertices, indices);
	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-1, 1,  1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-1, -1,  -1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(1, -1,  -1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-1, 1,  -1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1, 1, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("yellowcube", vertices, indices);
	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(-1, 1,  1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(-1, -1,  -1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(1, -1,  -1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(-1, 1,  -1), glm::vec3(1.0 ,0.5, 0.0)),
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1.0 ,0.5, 0.0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("orangecube", vertices, indices);
	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(-1, 1,  1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(-1, -1,  -1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(1, -1,  -1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(-1, 1,  -1), glm::vec3(0 ,1, 0.0)),
			VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(0 ,1, 0.0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("greencube", vertices, indices);
	}
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab6");
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("Shadersphere");
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/Spherevertex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/Spherefragment.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

Mesh* Laborator6::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Laborator6::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator6::Update(float deltaTimeSeconds)
{
	modelsphere = glm::mat4(1);//resetez sfera pt ca nu stiu daca acum a atins o platforma sau am pierdut jocul

	if (cameratype == 1)
		camera->Set(glm::vec3(0, 4, sz - 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));//third person
	else
		camera->Set(glm::vec3(sx, sy , sz-5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));//first person
	
	
	cout << "combustibil=";
	cout << fuel;
	cout << "\n";

	//aici time e folosit pt cand am atins o platforma portocalie si w si s nu mai merg
	if(time>0)
	time--;
	if (time == 0) {
		blocked = 0;
		
	}
	//daca platformele sunt in spatele bilei atunci le plasez in fata bilei ca sa stiu ce urmeaza si le schimb culorile cu vecotorul random
	if (c1z < -19){
		c1z = 21;
		
		for (int i = 0;i < 5;i++) {
			random[i] = rand() / 30 % 5;
			
		}
	}
	//la fel doar pt setul al doilea de platforme
	if (c2z < -19) {
		c2z = 21;
		
		for (int i = 0;i < 5;i++) {
			
			random2[i] = rand() / 30 % 5;
		}
	}
	//resetez indicatoru care imi arata ce fel de platforma este v pt primu set si w pt setul al doilea
	for (int j = 0;j < 5;j++) {
		v[j] = 0;
		w[j] = 0;
	}
	//primul set de platforme
	for (int j = 0;j < 5;j++)
	{
		for (int i = 0;i < 20;i++) {
			
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posx[j], c1y, c1z + i));
		
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			
			switch (random[j]) {
			case 0:
				RenderSimpleMesh(meshes["redcube"], shaders["ShaderLab6"], modelMatrix);
				v[j] = 1;
				break;
			case 1:
				RenderSimpleMesh(meshes["yellowcube"], shaders["ShaderLab6"], modelMatrix);
				v[j] = 2;
				break;
			case 2:
				RenderSimpleMesh(meshes["orangecube"], shaders["ShaderLab6"], modelMatrix);
				v[j] = 3;
				break;
			case 3:
				RenderSimpleMesh(meshes["greencube"], shaders["ShaderLab6"], modelMatrix);
				v[j] = 4;
				break;

			case 4:
				RenderSimpleMesh(meshes["bluecube"], shaders["ShaderLab6"], modelMatrix);
				v[j] = 5;
				break;

			}
		


			
			
			
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.01f));
			if ((SphereRectCollision(sx, sy, sz, posx[j], c1y, c1z + i) && v[j] >= 1)) {
				
				RenderSimpleMesh(meshes["purplecube"], shaders["ShaderLab6"], modelMatrix);

				if (v[j] == 1) 
				{ endgame = 1; }

				if (v[j] == 2&&fuel>=0) {
					fuel -= 1;
				
				}
				if (v[j] == 3) {
					blocked = 1;
				}
				if (v[j] == 4) {
					fuel += 1;
				}



			}




		}
	}
	//setul al doilea de platforme care initial sunt in fata celor de dinainte
	for (int j = 0;j < 5;j++)
	{
		for (int i = 0;i < 20;i++) {
		
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posx[j], c1y, c2z + i));
			
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			
			switch (random2[j]) {
			case 0: 
				RenderSimpleMesh(meshes["redcube"], shaders["ShaderLab6"], modelMatrix);
				w[j] = 1;
				break;
			case 1:
				RenderSimpleMesh(meshes["yellowcube"], shaders["ShaderLab6"], modelMatrix);
				w[j] = 2;
				break;
			case 2:
				RenderSimpleMesh(meshes["orangecube"], shaders["ShaderLab6"], modelMatrix);
				w[j] = 3;
				break;
			case 3:
				RenderSimpleMesh(meshes["greencube"], shaders["ShaderLab6"], modelMatrix);
				w[j]=4;
				break;
			case 4:
				RenderSimpleMesh(meshes["bluecube"], shaders["ShaderLab6"], modelMatrix);
				w[j] = 5;
				break;

			}



		

			
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.01f));
			if ((SphereRectCollision(sx, sy, sz, posx[j], c1y, c2z + i) && w[j] >= 1)) {
				
				RenderSimpleMesh(meshes["purplecube"], shaders["ShaderLab6"], modelMatrix);
				if (w[j] == 1)
				{
					endgame = 1;
				}

				if (w[j] == 2&&fuel>=0) {
					fuel -= 1;
				}
				if (w[j] == 3) {
					blocked = 1;
					time = 60;
				}
				if (w[j] == 4) {
					fuel += 1;
				}

			}




		}
	}
	
	
		
		modelsphere = glm::translate(modelsphere, glm::vec3(sx, sy, sz));
		modelsphere = glm::rotate(modelsphere, RADIANS(45.0f), glm::vec3(0, 1, 0));
		
		if (cameratype ==1 )
			
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab6"], modelsphere);
		
			
		//de aici verific daca a facut coliziune cu una din cele 2 seturi de coloane atunci nu trebuie sa cada sfera
		atins = 0;
		for (int j = 0;j < 5;j++)
		
			for (int i = 0;i < 20;i++) {
				if ((SphereRectCollision(sx, sy, sz, posx[j], c1y, c1z + i) && v[j] >=1 ) || (SphereRectCollision(sx, sy, sz, posx[j], c1y, c2z + i) && w[j]>= 1))
				{
					atins = 1;
					
				}
				
					
				
			}
		if (atins == 0) { sy = sy-ty/2; }//cade sfera altfel o deformez 
		else{
			modelsphere = glm::scale(modelsphere, glm::vec3(0.5f));
			modelsphere = glm::scale(modelsphere, glm::vec3(0.5f));
			
			if (cameratype == 1)
				
			RenderSimpleMesh(meshes["sphere"], shaders["Shadersphere"], modelsphere);
		}


	

	if (sy > 0 &&endgame==0) {//daca nu am pierdut si sunt deasupra prgului 0 atunci continui jocu plasand platformele in spate
		
		c1z -= speed * deltaTimeSeconds / 10;
		c2z -= speed * deltaTimeSeconds / 10;
		fuel -= speed * deltaTimeSeconds / 10;
		
		
	}
	else {//altfel deformeaza mult sfera
		
		modelsphere = glm::scale(modelsphere, glm::vec3(2.5f));
			RenderSimpleMesh(meshes["sphere"], shaders["Shadersphere"], modelsphere);
		cout << "YOU LOSE";
	}


}

void Laborator6::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator6::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator6::OnInputUpdate(float deltaTime, int mods)
{
	// add key press event


}

void Laborator6::OnKeyPress(int key, int mods)
{
	if (window->KeyHold(32)&& fuel>=5 && endgame==0) { //space
		sy += 2;
		fuel = fuel - 5;
		if (cameratype == 0)
			camera->TranslateUpword(2);
	}
	if (window->KeyHold(68)&& endgame==0 ) { //D
		sx -= 1;
		if (cameratype == 0)
			camera->TranslateRight(2);
	}
	if (window->KeyHold(65) && endgame==0) { //A
		sx += 1;
		if (cameratype == 0)
			camera->TranslateRight(-2);
	}
	if (window->KeyHold(87)&&blocked==0 && endgame==0) { //W
		
		speed+=10;
	}
	if (window->KeyHold(83)&&blocked==0 && endgame==0) { //S
		speed-=10;
	}
	if (window->KeyHold(67)) { //C
		if (cameratype == 1)
			cameratype = 0;
		else cameratype = 1;
	}








	// add key press event
}

void Laborator6::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator6::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator6::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator6::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator6::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator6::OnWindowResize(int width, int height)
{
}

bool Laborator6::SphereRectCollision(float sx, float sy, float sz, float tx, float ty, float tz)
{
	
	float sphereXDistance = abs(sx - tx);
	float sphereYDistance = abs(sy - ty);
	float sphereZDistance = abs(sz - tz);

	if (sphereXDistance >= (1)) { return false; }
	if (sphereYDistance >= (1)) { return false; }
	if (sphereZDistance >= (1,1)) { return false; }

	if (sphereXDistance < (1)) { return true; }
	if (sphereYDistance < (1)) { return true; }
	if (sphereZDistance < (1,1)) { return true; }

	float cornerDistance_sq = ((sphereXDistance - 1) * (sphereXDistance - 1)) +
		((sphereYDistance -1) * (sphereYDistance - 1) +
			((sphereZDistance -1) * (sphereZDistance -1)));

	return (cornerDistance_sq < (2));
}
