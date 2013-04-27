assert 'default constructor' do
	Vec2.new(1) != nil
end

assert 'constructor setting empty value' do
	value = Vec2.new
	value.x == 0 && value.y == 0
end

assert 'constructor setting single value' do
	value = Vec2.new(1)
	value.x == 1 && value.y == 1
end

assert 'constructor setting values' do
	value = Vec2.new(1, 2)
	value.x == 1 && value.y == 2
end

assert 'get x property' do
	vec = Vec2.new(5)
	vec.x == 5
end

assert 'set x property' do
	vec = Vec2.new(5)
	vec.x = 2
	vec.x == 2
end

assert 'get y property' do
	vec = Vec2.new(5)
	vec.y == 5
end

assert 'set y property' do
	vec = Vec2.new(5)
	vec.y = 2
	vec.y == 2
end

assert 'addition' do
	value = Vec2.new(0, 1) + Vec2.new(1, 0)
	value.x == 1 && value.y == 1
end

assert 'multiplication' do
	value = Vec2.new(1) * Vec2.new(3)
	value.x == 3 && value.y == 3
end

assert 'float multiplication' do
	value = Vec2.new(1) * 3
	value.x == 3 && value.y == 3
end

assert 'multiplication is not destructive' do
	original = Vec2.new(1)
	value = original * Vec2.new(3, 3)
	original.x == 1 && original.y == 1
end

assert 'subtraction' do
	value = Vec2.new(3) - Vec2.new(2)
	value.x == 1 && value.y == 1
end

assert 'division' do
	value = Vec2.new(4) / Vec2.new(2)
	value.x == 2 && value.y == 2
end

assert 'float division' do
	value = Vec2.new(4) / 2
	value.x == 2 && value.y == 2
end

assert 'equality' do
	Vec2.new(1, 2) == Vec2.new(1, 2)
end

assert 'inequality' do
	Vec2.new(1, 2) != Vec2.new(1, 3)
end

assert 'normalize' do
	value = Vec2.new(0, 5).normalize
	value.x == 0 && value.y == 1
end

assert 'length' do
	value = Vec2.new(0, 3).length
	value == 3
end

assert 'distance' do
	value = Vec2.new(3).distance_to(Vec2.new(3, 6))
	value == 3
end

assert 'dot' do
	value = Vec2.new(3).dot(Vec2.new(3, 4))
	value == 21
end