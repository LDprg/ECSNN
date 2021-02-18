#pragma once

struct nodeFirst
{
};

struct nodeHidden
{
};

struct nodeLast
{
};

struct nodelinear
{
};

struct nodetanh
{
};

struct nodebinary
{
	float level;
};

struct node
{
	int id;
	int layer;

	float input;
	float output;
};