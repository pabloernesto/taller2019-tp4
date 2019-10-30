#include "TrackPiece.h"

const b2Vec2 TrackPiece::TRACKPIECE_SIZE(3, 3);
const float32 TrackPiece::TRACKPIECE_WEIGHT = 10000;

TrackPiece::TrackPiece(){
}

void TrackPiece::Place(b2World& world, b2Vec2 position){
  // Add trackpiece to the world
  b2BodyDef trackPiece_body_def;
  trackPiece_body_def.type = b2_dynamicBody;
  trackPiece_body_def.position = position;
  body = world.CreateBody(&trackPiece_body_def);

  // Add collision and density to the trackpiece
  b2PolygonShape collision_box;
  collision_box.SetAsBox(TRACKPIECE_SIZE.x/2, TRACKPIECE_SIZE.y/2);

  b2FixtureDef trackPiece_fixture_def;
  trackPiece_fixture_def.shape = &collision_box;
  const float32 DENSITY = TRACKPIECE_WEIGHT / (TRACKPIECE_SIZE.x * TRACKPIECE_SIZE.y);
  trackPiece_fixture_def.density = DENSITY;
  body->CreateFixture(&trackPiece_fixture_def);
}

const b2Vec2& TrackPiece::GetPosition(){
  return body->GetPosition();
}