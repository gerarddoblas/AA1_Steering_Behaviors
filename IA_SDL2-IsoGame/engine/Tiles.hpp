#pragma once
//El struct de tiles gestiona la posició al mapa i res més
struct Tiles
{
public:
	int x;
	int y;

	bool operator==(Tiles tiles) { return (this->x == tiles.x && this->y == tiles.y); }
};