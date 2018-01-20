#pragma once

#include "3rdPartyLibs\glm\glm\glm.hpp"
#include "3rdPartyLibs\glm\glm\gtx\transform.hpp"
#include "3rdPartyLibs\glm\glm\matrix.hpp"
#include "Shader.h"


class ModelMatrix
{
public:
	Shader shader;

	glm::mat4 GetModel()
	{
		shader.UseProgram();
		return model;
	}

	void SetMatrix(glm::mat4 mvp)
	{
		shader.UseProgram();
		shader.SetMatrix(mvp);
	}

	void Render() const
	{
		//shader.UseProgram();
		glDrawArrays(GL_TRIANGLES, 0, 3); // positions.size()
	}

	void ResetMatrix()
	{
		model = glm::mat4(1.0f);
		rotate = glm::mat4(1.0f);
		scale = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);
	}

	void Translate(const glm::vec3 &axis)
	{
		translate = glm::translate(translate, axis);
		UpdateMatrix();
	}

	void Rotate(glm::vec3 axis, double angle)
	{
		//rotate = glm::rotate(rotate, angle, axis);
		UpdateMatrix();
	}

	void Scale(glm::vec3 axis)
	{
		scale = glm::scale(scale, axis);
		UpdateMatrix();
	}

	void UpdateMatrix()
	{
		model = scale * translate * rotate;
	}

private:
	glm::mat4 model;
	glm::mat4 rotate;
	glm::mat4 translate;
	glm::mat4 scale;
};