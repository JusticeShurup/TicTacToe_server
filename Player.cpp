#include "Player.h"
#include "ClientConnectedState.h"
#include "Game.h"
#include <stdexcept>

Player::Player(Poco::Net::StreamSocket& client, Server* server) :
	socket(client),
	server(server),
	game(nullptr),
	state(new ClientConnectedState(this)),
	is_ready(false), 
	nickname("player"), 
	game_number(0)
{}

Player::~Player() {
	delete state;
}

void Player::setState(State* new_state) {
	delete state;
	state = new_state;
}

Server* Player::getServer() const {
	return server;
}

Game* Player::getGame() const {
	if (!this->game) throw std::runtime_error("Player isn't playing in game");
	return game;
}

void Player::setGame(Game* game) {
	if (this->game) throw std::runtime_error("Player is already playing something");
	this->game = game;
}

void Player::setNickname(std::string nickname) {
	this->nickname = nickname;
}

std::string Player::getNickname() const{
	return nickname;
}

void Player::handleRead(Poco::Net::StreamSocket socket) {
	state->handleRead(socket);
}

bool Player::get_ready() const{
	return is_ready;
}

void Player::set_ready(bool is_ready) {
	this->is_ready = is_ready;
}

int Player::get_gameNumber() const {
	return game_number;
}

void Player::set_gameNumber(int game_number) {
	if (game_number > 2 || game_number < 1) throw std::range_error("Incorrect game number");
	this->game_number = game_number;
}