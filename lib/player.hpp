#pragma once

#include "common.hpp"
#include "field.hpp"
#include "ship.hpp"

class Player {
  friend class AddCellCommand;

 public:
  Player(size_t index, const Vector2u& size);
  ~Player() = default;

  void Clear();
  size_t GetIndex() const;
  ShotState GetLastShotResult() const;
  size_t GetShipCount() const;
  MyField* GetMField();
  RivalField* GetRField();
  void DecrementShipCount();
  void AddShip();
  void Shoot(Cell* cell, ShotState& shot_result);
  const Ship* GetShipInProcess() const;
  size_t GetNumberOfShips(size_t size) const;
  void LinkWithRival(Player* rival);
  Player* GetRival();

 protected:
  size_t m_index;
  ShotState m_last_shot_state;
  size_t m_ship_count;
  MyField m_field_m;
  RivalField m_field_r;
  deque<deque<Ship>> m_ships;
  Ship m_ship_in_process;
  Player* m_rival;
};
