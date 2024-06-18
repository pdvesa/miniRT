/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:33:09 by svesa             #+#    #+#             */
/*   Updated: 2024/06/18 19:33:27 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	print_all(t_scene *scene)
{
	int i = 0;
	
	if (scene->ambient_light)
	{
		printf("Ambient\n");
		printf("\tAmbient ratio: %f\n", scene->ambient_light->ratio);
		printf("\tAmbient color red: %d\n", scene->ambient_light->rgb.r);
		printf("\tAmbient color green: %d\n", scene->ambient_light->rgb.g);
		printf("\tAmbient color blue: %d\n", scene->ambient_light->rgb.b);
	}
	if (scene->camera)
	{
		printf("Camera\n");
		printf("\tCamera cord x: %f\n", scene->camera->center.x);
		printf("\tCamera cord y: %f\n", scene->camera->center.y);
		printf("\tCamera cord z: %f\n", scene->camera->center.z);
		printf("\tCamera vector x: %f\n", scene->camera->vector.x);
		printf("\tCamera vector y: %f\n", scene->camera->vector.y);
		printf("\tCamera vector z: %f\n", scene->camera->vector.z);
		printf("\tFOV: %d\n", scene->camera->fov);
	}
	if (scene->light)
	{
		printf("Light\n");
		printf("\tLight cord x : %f\n", scene->light->center.x);
		printf("\tLight cord x : %f\n", scene->light->center.y);
		printf("\tLight cord x : %f\n", scene->light->center.z);
		printf("\tBrightness : %f\n", scene->light->brightness);
		// printf("Light color r: %d\n", i, scene->light->rgb.r);
		// printf("Light color g: %d\n", i, scene->light->rgb.g);
		// printf("Light color b: %d\n", i, scene->light->rgb.b);
	}
	if (scene->sphere)
	{
		printf("Sphere(s)\n");
		while(scene->sphere[i])
		{
			if (i)
				printf("Next one\n");
			printf("\tSphere %d cord x: %f\n", i, scene->sphere[i]->center.x);
			printf("\tSphere %d cord x: %f\n", i, scene->sphere[i]->center.y);
			printf("\tSphere %d cord x: %f\n", i, scene->sphere[i]->center.z);
			printf("\tSphere %d diameter: %f\n", i, scene->sphere[i]->diameter);
			printf("\tSphere %d color r: %d\n", i, scene->sphere[i]->rgb.r);
			printf("\tSphere %d color g: %d\n", i, scene->sphere[i]->rgb.g);
			printf("\tSphere %d color b: %d\n", i, scene->sphere[i]->rgb.b);
			i++;
		}
	}
	if (scene->plane)
	{
		i = 0;
		printf("Plane(s)\n");
		while(scene->plane[i])
		{
			if (i)
				printf("Next one\n");
			printf("\tPlane %d cord x: %f\n", i, scene->plane[i]->coordinates.x);
			printf("\tPlane %d cord x: %f\n", i, scene->plane[i]->coordinates.y);
			printf("\tPlane %d cord x: %f\n", i, scene->plane[i]->coordinates.z);
			printf("\tPlane %d vector x: %f\n", i, scene->plane[i]->vector.x);
			printf("\tPlane %d vector y: %f\n", i, scene->plane[i]->vector.y);
			printf("\tPlane %d vector z: %f\n", i, scene->plane[i]->vector.z);
			printf("\tPlane %d color r: %d\n", i, scene->plane[i]->rgb.r);
			printf("\tPlane %d color g: %d\n", i, scene->plane[i]->rgb.g);
			printf("\tPlane %d color b: %d\n", i, scene->plane[i]->rgb.b);
			i++;
		}
	}
	if (scene->cylinder)
	{
		i = 0;
		printf("Cylinder(s)\n");
		while(scene->cylinder[i])
		{
			if (i)
				printf("Next one\n");
			printf("\tCylinder %d cord x: %f\n", i, scene->cylinder[i]->center.x);
			printf("\tCylinder %d cord x: %f\n", i, scene->cylinder[i]->center.y);
			printf("\tCylinder %d cord x: %f\n", i, scene->cylinder[i]->center.z);
			printf("\tCylinder %d vector x: %f\n", i, scene->cylinder[i]->vector.x);
			printf("\tCylinder %d vector y: %f\n", i, scene->cylinder[i]->vector.y);
			printf("\tCylinder %d vector z: %f\n", i, scene->cylinder[i]->vector.z);
			printf("\tCylinder %d diameter: %f\n", i, scene->cylinder[i]->diameter);
			printf("\tCylinder %d height: %f\n", i, scene->cylinder[i]->height);
			printf("\tCylinder %d color r: %d\n", i, scene->cylinder[i]->rgb.r);
			printf("\tCylinder %d color g: %d\n", i, scene->cylinder[i]->rgb.g);
			printf("\tCylinder %d color b: %d\n", i, scene->cylinder[i]->rgb.b);
			i++;
		}
	}
}