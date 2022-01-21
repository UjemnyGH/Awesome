#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../Buffers/Aws_Buffer.hpp"
#include "../stb_image/stb_easy_font.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "../stb_image/stb_image.h"
#include "../Aws_Types.hpp"

namespace AWS
{
	TextureAtlasData textCoords[41] = {
		TextureAtlasData(1.0f, 8.0f, 0.0f, 8.0f, 1.0f, 7.0f, 0.0f, 8.0f, 1.0f, 7.0f, 0.0f, 7.0f),
		TextureAtlasData(2.0f, 8.0f, 1.0f, 8.0f, 2.0f, 7.0f, 1.0f, 8.0f, 2.0f, 7.0f, 1.0f, 7.0f),
		TextureAtlasData(3.0f, 8.0f, 2.0f, 8.0f, 3.0f, 7.0f, 2.0f, 8.0f, 3.0f, 7.0f, 2.0f, 7.0f),
		TextureAtlasData(4.0f, 8.0f, 3.0f, 8.0f, 4.0f, 7.0f, 3.0f, 8.0f, 4.0f, 7.0f, 3.0f, 7.0f),
		TextureAtlasData(5.0f, 8.0f, 4.0f, 8.0f, 5.0f, 7.0f, 4.0f, 8.0f, 5.0f, 7.0f, 4.0f, 7.0f),
		TextureAtlasData(6.0f, 8.0f, 5.0f, 8.0f, 6.0f, 7.0f, 5.0f, 8.0f, 6.0f, 7.0f, 5.0f, 7.0f),
		TextureAtlasData(7.0f, 8.0f, 6.0f, 8.0f, 7.0f, 7.0f, 6.0f, 8.0f, 7.0f, 7.0f, 6.0f, 7.0f),
		TextureAtlasData(8.0f, 8.0f, 7.0f, 8.0f, 8.0f, 7.0f, 7.0f, 8.0f, 8.0f, 7.0f, 7.0f, 7.0f),

		TextureAtlasData(1.0f, 7.0f, 0.0f, 7.0f, 1.0f, 6.0f, 0.0f, 7.0f, 1.0f, 6.0f, 0.0f, 6.0f),
		TextureAtlasData(2.0f, 7.0f, 1.0f, 7.0f, 2.0f, 6.0f, 1.0f, 7.0f, 2.0f, 6.0f, 1.0f, 6.0f),
		TextureAtlasData(3.0f, 7.0f, 2.0f, 7.0f, 3.0f, 6.0f, 2.0f, 7.0f, 3.0f, 6.0f, 2.0f, 6.0f),
		TextureAtlasData(4.0f, 7.0f, 3.0f, 7.0f, 4.0f, 6.0f, 3.0f, 7.0f, 4.0f, 6.0f, 3.0f, 6.0f),
		TextureAtlasData(5.0f, 7.0f, 4.0f, 7.0f, 5.0f, 6.0f, 4.0f, 7.0f, 5.0f, 6.0f, 4.0f, 6.0f),
		TextureAtlasData(6.0f, 7.0f, 5.0f, 7.0f, 6.0f, 6.0f, 5.0f, 7.0f, 6.0f, 6.0f, 5.0f, 6.0f),
		TextureAtlasData(7.0f, 7.0f, 6.0f, 7.0f, 7.0f, 6.0f, 6.0f, 7.0f, 7.0f, 6.0f, 6.0f, 6.0f),
		TextureAtlasData(8.0f, 7.0f, 7.0f, 7.0f, 8.0f, 6.0f, 7.0f, 7.0f, 8.0f, 6.0f, 7.0f, 6.0f),

		TextureAtlasData(1.0f, 6.0f, 0.0f, 6.0f, 1.0f, 5.0f, 0.0f, 6.0f, 1.0f, 5.0f, 0.0f, 5.0f),
		TextureAtlasData(2.0f, 6.0f, 1.0f, 6.0f, 2.0f, 5.0f, 1.0f, 6.0f, 2.0f, 5.0f, 1.0f, 5.0f),
		TextureAtlasData(3.0f, 6.0f, 2.0f, 6.0f, 3.0f, 5.0f, 2.0f, 6.0f, 3.0f, 5.0f, 2.0f, 5.0f),
		TextureAtlasData(4.0f, 6.0f, 3.0f, 6.0f, 4.0f, 5.0f, 3.0f, 6.0f, 4.0f, 5.0f, 3.0f, 5.0f),
		TextureAtlasData(5.0f, 6.0f, 4.0f, 6.0f, 5.0f, 5.0f, 4.0f, 6.0f, 5.0f, 5.0f, 4.0f, 5.0f),
		TextureAtlasData(6.0f, 6.0f, 5.0f, 6.0f, 6.0f, 5.0f, 5.0f, 6.0f, 6.0f, 5.0f, 5.0f, 5.0f),
		TextureAtlasData(7.0f, 6.0f, 6.0f, 6.0f, 7.0f, 5.0f, 6.0f, 6.0f, 7.0f, 5.0f, 6.0f, 5.0f),
		TextureAtlasData(8.0f, 6.0f, 7.0f, 6.0f, 8.0f, 5.0f, 7.0f, 6.0f, 8.0f, 5.0f, 7.0f, 5.0f),

		TextureAtlasData(1.0f, 5.0f, 0.0f, 5.0f, 1.0f, 4.0f, 0.0f, 5.0f, 1.0f, 4.0f, 0.0f, 4.0f),
		TextureAtlasData(2.0f, 5.0f, 1.0f, 5.0f, 2.0f, 4.0f, 1.0f, 5.0f, 2.0f, 4.0f, 1.0f, 4.0f),
		TextureAtlasData(3.0f, 5.0f, 2.0f, 5.0f, 3.0f, 4.0f, 2.0f, 5.0f, 3.0f, 4.0f, 2.0f, 4.0f),
		TextureAtlasData(4.0f, 5.0f, 3.0f, 5.0f, 4.0f, 4.0f, 3.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f),
		TextureAtlasData(5.0f, 5.0f, 4.0f, 5.0f, 5.0f, 4.0f, 4.0f, 5.0f, 5.0f, 4.0f, 4.0f, 4.0f),
		TextureAtlasData(6.0f, 5.0f, 5.0f, 5.0f, 6.0f, 4.0f, 5.0f, 5.0f, 6.0f, 4.0f, 5.0f, 4.0f),
		TextureAtlasData(7.0f, 5.0f, 6.0f, 5.0f, 7.0f, 4.0f, 6.0f, 5.0f, 7.0f, 4.0f, 6.0f, 4.0f),
		TextureAtlasData(8.0f, 5.0f, 7.0f, 5.0f, 8.0f, 4.0f, 7.0f, 5.0f, 8.0f, 4.0f, 7.0f, 4.0f),

		TextureAtlasData(1.0f, 4.0f, 0.0f, 4.0f, 1.0f, 3.0f, 0.0f, 4.0f, 1.0f, 3.0f, 0.0f, 3.0f),
		TextureAtlasData(2.0f, 4.0f, 1.0f, 4.0f, 2.0f, 3.0f, 1.0f, 4.0f, 2.0f, 3.0f, 1.0f, 3.0f),
		TextureAtlasData(3.0f, 4.0f, 2.0f, 4.0f, 3.0f, 3.0f, 2.0f, 4.0f, 3.0f, 3.0f, 2.0f, 3.0f),
		TextureAtlasData(4.0f, 4.0f, 3.0f, 4.0f, 4.0f, 3.0f, 3.0f, 4.0f, 4.0f, 3.0f, 3.0f, 3.0f),
		TextureAtlasData(5.0f, 4.0f, 4.0f, 4.0f, 5.0f, 3.0f, 4.0f, 4.0f, 5.0f, 3.0f, 4.0f, 3.0f),
		TextureAtlasData(6.0f, 4.0f, 5.0f, 4.0f, 6.0f, 3.0f, 5.0f, 4.0f, 6.0f, 3.0f, 5.0f, 3.0f),
		TextureAtlasData(7.0f, 4.0f, 6.0f, 4.0f, 7.0f, 3.0f, 6.0f, 4.0f, 7.0f, 3.0f, 6.0f, 3.0f),
		TextureAtlasData(8.0f, 4.0f, 7.0f, 4.0f, 8.0f, 3.0f, 7.0f, 4.0f, 8.0f, 3.0f, 7.0f, 3.0f),

		TextureAtlasData(8.0f, 1.0f, 7.0f, 1.0f, 8.0f, 0.0f, 7.0f, 1.0f, 8.0f, 0.0f, 7.0f, 0.0f)
	};

	std::map<char, int> letters = {
		{'A', 0},
		{'B', 1},
		{'C', 2},
		{'D', 3},
		{'E', 4},
		{'F', 5},
		{'G', 6},
		{'H', 7},
		{'I', 8},
		{'J', 9},
		{'K', 10},
		{'L', 11},
		{'M', 12},
		{'N', 13},
		{'O', 14},
		{'P', 15},
		{'R', 16},
		{'S', 17},
		{'T', 18},
		{'U', 19},
		{'W', 20},
		{'Y', 21},
		{'Z', 22},
		{'X', 23},
		{'Q', 24},
		{'V', 25},
		{'a', 0},
		{'b', 1},
		{'c', 2},
		{'d', 3},
		{'e', 4},
		{'f', 5},
		{'g', 6},
		{'h', 7},
		{'i', 8},
		{'j', 9},
		{'k', 10},
		{'l', 11},
		{'m', 12},
		{'n', 13},
		{'o', 14},
		{'p', 15},
		{'r', 16},
		{'s', 17},
		{'t', 18},
		{'u', 19},
		{'w', 20},
		{'y', 21},
		{'z', 22},
		{'x', 23},
		{'q', 24},
		{'v', 25},
		{':', 26},
		{'!', 27},
		{'?', 28},
		{'.', 29},
		{'1', 30},
		{'2', 31},
		{'3', 32},
		{'4', 33},
		{'5', 34},
		{'6', 35},
		{'7', 36},
		{'8', 37},
		{'9', 38},
		{'0', 39},
		{'\0', 29},
		{'\n', 29},
		{' ', 40}
	};

	class Aws_Text
	{
	private:
		unsigned int sh, vao, vbo[3], tex, text_size;

		glm::mat4 transform;

		std::vector<float> vertices = { 1.0f };
		std::vector<float> texCoords = { 1.0f };
		std::vector<float> color = { 1.0f };

		float psr[3][3] = {
			{0.0f, 0.0f, 0.0f},
			{1.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 0.0f}
		};

	public:
		void Init();
		void SetText(std::string text, float r, float g, float b, float a);
		void TextAtlas(const char* text_atlas);
		void Pos(float x, float y, float z);
		void Scl(float x, float y, float z);
		void Rot(float x, float y, float z);
		void Draw(glm::mat4 proj = glm::mat4(1.0), glm::mat4 view = glm::mat4(1.0));
		void Terminate();
	};

	void Aws_Text::Init()
	{
		sh = glCreateProgram();
		glAttachShader(sh, ShaderFromCode(vsAtlas, GL_VERTEX_SHADER));
		glAttachShader(sh, ShaderFromCode(fsAtlas, GL_FRAGMENT_SHADER));
		glLinkProgram(sh);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(3, vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(float), color.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(2);

		glGenTextures(1, &tex);

		int x, y, bit;

		stbi_set_flip_vertically_on_load(1);
		auto* data = stbi_load("data/texture/characterAtlas.png", &x, &y, &bit, STBI_rgb_alpha);

		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		glUseProgram(sh);

		glUniform1i(glGetUniformLocation(sh, "textures"), 0);

		glUseProgram(0);

		glBindVertexArray(0);
	}

	void Aws_Text::SetText(std::string text, float r, float g, float b, float a)
	{
		text_size = text.size();

		const char* chText = text.c_str();

		vertices.clear();
		texCoords.clear();
		color.clear();

		for (int size = 0; size <= text_size; size++)
		{
			vertices.push_back(0.05f + (0.05f * size * 1.01f));
			vertices.push_back(0.05f);
			vertices.push_back(0.0f);

			texCoords.push_back(textCoords[letters[chText[size]]].x0 * sizeAtlas128);
			texCoords.push_back(textCoords[letters[chText[size]]].y0 * sizeAtlas128);

			color.push_back(r);
			color.push_back(g);
			color.push_back(b);
			color.push_back(a);

			vertices.push_back(-0.05f + (0.05f * size * 1.01f));
			vertices.push_back(0.05f);
			vertices.push_back(0.0f);

			texCoords.push_back(textCoords[letters[chText[size]]].x1 * sizeAtlas128);
			texCoords.push_back(textCoords[letters[chText[size]]].y1 * sizeAtlas128);

			color.push_back(r);
			color.push_back(g);
			color.push_back(b);
			color.push_back(a);

			vertices.push_back(0.05f + (0.05f * size * 1.01f));
			vertices.push_back(-0.05f);
			vertices.push_back(0.0f);

			texCoords.push_back(textCoords[letters[chText[size]]].x2 * sizeAtlas128);
			texCoords.push_back(textCoords[letters[chText[size]]].y2 * sizeAtlas128);

			color.push_back(r);
			color.push_back(g);
			color.push_back(b);
			color.push_back(a);

			vertices.push_back(-0.05f + (0.05f * size * 1.01f));
			vertices.push_back(0.05f);
			vertices.push_back(0.0f);

			texCoords.push_back(textCoords[letters[chText[size]]].x3 * sizeAtlas128);
			texCoords.push_back(textCoords[letters[chText[size]]].y3 * sizeAtlas128);

			color.push_back(r);
			color.push_back(g);
			color.push_back(b);
			color.push_back(a);

			vertices.push_back(0.05f + (0.05f * size * 1.01f));
			vertices.push_back(-0.05f);
			vertices.push_back(0.0f);

			texCoords.push_back(textCoords[letters[chText[size]]].x4 * sizeAtlas128);
			texCoords.push_back(textCoords[letters[chText[size]]].y4 * sizeAtlas128);

			color.push_back(r);
			color.push_back(g);
			color.push_back(b);
			color.push_back(a);

			vertices.push_back(-0.05f + (0.05f * size * 1.01f));
			vertices.push_back(-0.05f);
			vertices.push_back(0.0f);

			texCoords.push_back(textCoords[letters[chText[size]]].x5 * sizeAtlas128);
			texCoords.push_back(textCoords[letters[chText[size]]].y5 * sizeAtlas128);

			color.push_back(r);
			color.push_back(g);
			color.push_back(b);
			color.push_back(a);
		}

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(float), color.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void Aws_Text::TextAtlas(const char* text_atlas)
	{
		glBindVertexArray(vao);

		int x, y, bit;

		stbi_set_flip_vertically_on_load(1);
		auto* data = stbi_load(text_atlas, &x, &y, &bit, STBI_rgb_alpha);

		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		glBindVertexArray(0);
	}

	void Aws_Text::Pos(float x, float y, float z)
	{
		psr[0][0] = x;
		psr[0][1] = y;
		psr[0][2] = z;

		transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
		transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
	}

	void Aws_Text::Scl(float x, float y, float z)
	{
		psr[1][0] = x;
		psr[1][1] = y;
		psr[1][2] = z;

		transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
		transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
	}

	void Aws_Text::Rot(float x, float y, float z)
	{
		psr[2][0] = x;
		psr[2][1] = y;
		psr[2][2] = z;

		transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
		transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
	}

	void Aws_Text::Draw(glm::mat4 proj, glm::mat4 view)
	{
		glBindVertexArray(vao);
		glUseProgram(sh);

		glBindTexture(GL_TEXTURE_2D, tex);

		glUniformMatrix4fv(glGetUniformLocation(sh, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(sh, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(sh, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Aws_Text::Terminate()
	{
		glDeleteProgram(sh);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(3, vbo);
		glDeleteTextures(1, &tex);
	}

	typedef Aws_Text Text;
}