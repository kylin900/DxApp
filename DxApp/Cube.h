#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>

class Cube
{
public:
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		namespace dx = DirectX;

		constexpr float side = 1.0f / 2.0f;

		std::vector<dx::XMFLOAT3> vertices;
		vertices.emplace_back(-side, -side, -side); // 0
		vertices.emplace_back(side, -side, -side); // 1
		vertices.emplace_back(-side, side, -side); // 2
		vertices.emplace_back(side, side, -side); // 3
		vertices.emplace_back(-side, -side, side); // 4
		vertices.emplace_back(side, -side, side); // 5
		vertices.emplace_back(-side, side, side); // 6
		vertices.emplace_back(side, side, side); // 7

		std::vector<V> verts(vertices.size());
		for(size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
		}
		return{
			std::move(verts),{
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
			}
		};
	}
	template<class V>
	static IndexedTriangleList<V> MakeSkinned()
	{
		namespace dx = DirectX;

		constexpr float side = 1.0f / 2.0f;

		std::vector<V> vertices(24);

		vertices[0].pos = { -side, -side, -side };
		vertices[0].tex = { 0.0f, 1.0f };
		vertices[1].pos = { -side, +side, -side};
		vertices[1].tex = { 0.0f, 0.0f };
		vertices[2].pos = { +side, +side, -side };
		vertices[2].tex = { 1.0f, 0.0f };
		vertices[3].pos = { +side, -side, -side };
		vertices[3].tex = {  1.0f, 1.0f };

		vertices[4].pos = { -side, -side, +side };
		vertices[4].tex = {  1.0f, 1.0f };
		vertices[5].pos = { +side, -side, +side };
		vertices[5].tex = {  0.0f, 1.0f };
		vertices[6].pos = { +side, +side, +side};
		vertices[6].tex = {  0.0f, 0.0f };
		vertices[7].pos = { -side, +side, +side };
		vertices[7].tex = {  1.0f, 0.0f };

		vertices[8].pos = { -side, +side, -side };
		vertices[8].tex = {  0.0f, 1.0f };
		vertices[9].pos = { -side, +side, +side };
		vertices[9].tex = {  0.0f, 0.0f };
		vertices[10].pos = { +side, +side, +side };
		vertices[10].tex = {  1.0f, 0.0f };
		vertices[11].pos = { +side, +side, -side };
		vertices[11].tex = {  1.0f, 1.0f };

		vertices[12].pos = { -side, -side, -side };
		vertices[12].tex = {  1.0f, 1.0f };
		vertices[13].pos = { +side, -side, -side };
		vertices[13].tex = {  0.0f, 1.0f };
		vertices[14].pos = { +side, -side, +side };
		vertices[14].tex = {  0.0f, 0.0f };
		vertices[15].pos = { -side, -side, +side };
		vertices[15].tex = {  1.0f, 0.0f };

		vertices[16].pos = { -side, -side, +side };
		vertices[16].tex = {  0.0f, 1.0f };
		vertices[17].pos = { -side, +side, +side };
		vertices[17].tex = {  0.0f, 0.0f };
		vertices[18].pos = { -side, +side, -side };
		vertices[18].tex = {  1.0f, 0.0f };
		vertices[19].pos = { -side, -side, -side };
		vertices[19].tex = {  1.0f, 1.0f };

		vertices[20].pos = { +side, -side, -side };
		vertices[20].tex = { 0.0f, 1.0f };
		vertices[21].pos = { +side, +side, -side };
		vertices[21].tex = { 0.0f, 0.0f };
		vertices[22].pos = { +side, +side, +side };
		vertices[22].tex = { 1.0f, 0.0f };
		vertices[23].pos = { +side, -side, +side };
		vertices[23].tex = {  1.0f, 1.0f };

		return{
			std::move(vertices),{
				0,1,2,   0,2,3,
				4,5,6,   4,6,7,
				8,9,10,   8,10,11,
				12,13,14,   12,14,15,
				16,17,18, 16,18,19,
				20,21,22,  20,22,23
			}
		};
	}
};