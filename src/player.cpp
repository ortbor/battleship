#include "../lib/player.hpp"

#include "../lib/cell.hpp"

<<<<<<< HEAD
Player::Player(size_t index, const Vector2f& size)
    : index_(index),
      last_shot_result_(ShotResult::Unknown),
      ship_count_(0),
      my_field_(MyField(size)),
      rival_field_(RivalField(size)),
      ships_(deque<deque<Ship>>(5)),
      rival_(nullptr) {}

size_t Player::GetIndex() const { return index_; }

ShotResult Player::GetLastShotResult() const { return last_shot_result_; }

size_t Player::GetShipCount() const { return ship_count_; }

MyField* Player::GetField() { return &my_field_; }

RivalField* Player::GetRField() { return &rival_field_; }

void Player::DecrementShipCount() { --ship_count_; }

void Player::AddShip() {
  ships_[ship_in_process_.GetSize()].push_back(ship_in_process_);
  ++ship_count_;
  my_field_.SetShip(&*ships_[ship_in_process_.GetSize()].rbegin());
  ship_in_process_.Clear();
}

void Player::Shoot(Cell* cell, ShotResult& shot_result) {
  rival_field_.UpdateShot(cell, shot_result);
  if (shot_result == ShotResult::Kill) {
    rival_->DecrementShipCount();
  }
  last_shot_result_ = shot_result;
}

const Ship* Player::GetShipInProcess() const { return &ship_in_process_; }

size_t Player::GetNumberOfShips(size_t size) const {
  return ships_[size].size();
}

void Player::LinkWithRival(Player* rival) {
  rival_ = rival;
  rival->rival_ = this;
  my_field_.LinkField(&rival->rival_field_);
  rival_field_.LinkField(&rival->my_field_);
}

Player* Player::GetRival() { return rival_; }
||||||| 58d15e7
Player::Player(size_t index, const Vector2f& size)
    : index_(index),
      last_shot_result_(ShotResult::Unknown),
      ship_count_(0),
      my_field_(MyField(size)),
      rival_field_(RivalField(size)),
      ships_(deque<deque<Ship>>(5)),
      rival_(nullptr) {}

size_t Player::GetIndex() const { return index_; }

ShotResult Player::GetLastShotResult() const { return last_shot_result_; }

size_t Player::GetShipCount() const { return ship_count_; }

MyField* Player::GetField() { return &my_field_; }

RivalField* Player::GetRField() { return &rival_field_; }

void Player::DecrementShipCount() { --ship_count_; }

void Player::AddShip() {
  ships_[ship_in_process_.GetSize()].push_back(ship_in_process_);
  ++ship_count_;
  my_field_.SetShip(&*ships_[ship_in_process_.GetSize()].rbegin());
  ship_in_process_.Clear();
}

void Player::Shoot(Cell* cell, ShotResult& shot_result) {
  rival_field_.UpdateShot(cell, shot_result);
  if (shot_result == ShotResult::Kill) {
    rival_->DecrementShipCount();
  }
  last_shot_result_ = shot_result;
}

const Ship* Player::GetShipInProcess() const { return &ship_in_process_; }

size_t Player::GetNumberOfShipsSized(size_t size) const {
  return ships_[size].size();
}

void Player::LinkWithRival(Player* rival) {
  rival_ = rival;
  rival->rival_ = this;
  my_field_.LinkField(&rival->rival_field_);
  rival_field_.LinkField(&rival->my_field_);
}

Player* Player::GetRival() { return rival_; }
=======
Player::Player(size_t index, const Vector2u& size)
    : m_index(index),
      m_ship_count(0),
      m_field_m(MyField(size)),
      m_field_r(RivalField(size)),
      m_ships(deque<deque<Ship>>(5)),
      m_rival(nullptr) {}
>>>>>>> dev-ntheme

void Player::Clear() {
  m_field_m.Clear();
  m_field_r.Clear();
  for (int i = 0; i < 5; ++i) {
    m_ships[i].clear();
  }
  m_ship_in_process.Clear();
  m_ship_count = 0;
}

size_t Player::GetIndex() const { return m_index; }

size_t Player::GetShipCount() const { return m_ship_count; }

MyField* Player::GetMField() { return &m_field_m; }

RivalField* Player::GetRField() { return &m_field_r; }

void Player::DecrementShipCount() { --m_ship_count; }

void Player::AddShip() {
  m_ships[m_ship_in_process.GetSize()].push_back(m_ship_in_process);
  ++m_ship_count;
  m_field_m.SetShip(&*m_ships[m_ship_in_process.GetSize()].rbegin());
  m_ship_in_process.Clear();
}

ShotState Player::Shoot(Cell* cell) {
  ShotState shot_result = m_field_r.UpdateShot(cell);
  if (shot_result == ShotState::Kill) {
    m_rival->DecrementShipCount();
  }
  return shot_result;
}

const Ship* Player::GetShipInProcess() const { return &m_ship_in_process; }

size_t Player::GetNumShips(size_t size) const { return m_ships[size].size(); }

void Player::LinkWithRival(Player* rival) {
  m_rival = rival;
  rival->m_rival = this;
  m_field_m.LinkField(&rival->m_field_r);
  m_field_r.LinkField(&rival->m_field_m);
}

Player* Player::GetRival() { return m_rival; }
