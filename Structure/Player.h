struct Player {
  name: char *, // identité unique du joueur
  x: uint, // position x du joueur
  y: uint, // position y du joueur
  energy: uint, // énergie restante du joueur
  looking: uint, // direction dans laquelle regarde le joueur (left = 0, up = 1, right = 2, down = 3)
}
