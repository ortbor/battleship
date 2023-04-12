#include "../lib/cell.hpp"

Cell::Cell(const Vector2f& coord)
    : coord_(coord),
      state_(State::Unknown),
      ship_(nullptr),
      twin_cell_(nullptr),
      shape_(nullptr) {}

const Vector2f& Cell::GetCoord() const { return coord_; }

State Cell::GetState() const { return state_; }

Ship* Cell::GetShip() const { return ship_; }

Cell* Cell::GetTwin() const { return twin_cell_; }

sf::RectangleShape* Cell::GetShape() const { return shape_; }

void Cell::SetState(State state) {
  state_ = state;
  if (shape_ != nullptr) {
    UpdateColor();
  }
}

void Cell::SetShip(Ship* ship) { ship_ = ship; }

void Cell::SetTwins(Cell* other_cell) {
  twin_cell_ = other_cell;
  other_cell->twin_cell_ = this;
}

void Cell::SetShape(sf::RectangleShape* shape) { shape_ = shape; }

void Cell::UpdateColor() {
  switch (state_) {
    case State::Alive:
      shape_->setFillColor(Color(0, 135, 255));
      break;
    case State::Chosen:
      shape_->setFillColor(Color(0, 255 - 120, 0));
      break;
    case State::Clear:
      shape_->setFillColor(Color(255, 120, 255));
      break;
    case State::Prohibited:
      shape_->setFillColor(Color(255, 0, 0));
      break;
    default:
      throw std::runtime_error("Unknown state!");
      break;
  }
}

bool CellComparator(const Cell* cell1, const Cell* cell2) {
  return cell1->GetCoord().x < cell2->GetCoord().x ||
         (cell1->GetCoord().x == cell2->GetCoord().x &&
          cell1->GetCoord().y < cell2->GetCoord().y);
}
