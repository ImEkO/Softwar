struct GameInfo {
  map_size: uint,
  game_status: uint, // 0 => waiting, 1 => started, 2 => finished
  players: list<Player>,
  energy_cells: list<EnergyCell>
}
