#pragma once

constexpr auto WIDTH = 80;
constexpr auto HEIGHT = 30;

//Space Invaders
constexpr auto GROUND = HEIGHT - 1;
constexpr auto PLAYER = GROUND - 1;
constexpr short BARRIER = HEIGHT * 0.8;
constexpr short ALIENMOVEDIST = 2;
constexpr short ALIENMOVEFREQ = 3;
constexpr short DISTBETWEENALIENS = 3;
constexpr short AMOUNTOFBARRIERS = 20;
constexpr short AMOUNTOFALIENS = 20;
constexpr short MAXAMOUNTOFMISSILES = 5;
constexpr short MAXAMOUNTOFENEMYMISSILES = 10;
constexpr short MAXPLAYERSHOOTCOOLDOWN = 1;
constexpr short MAXENEMYSHOOTCOOLDOWN = 75;

//Frogger
constexpr auto STARTPAVEMENT = GROUND;
constexpr short CARMOVEFREQ = 3;
