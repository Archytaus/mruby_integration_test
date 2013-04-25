assert 'default constructor' do
	Vec3.new(1) != nil
end

assert 'get x property' do
	vec = Vec3.new(5)
	vec.x == 5
end

assert 'set x property' do
	vec = Vec3.new(5)
	vec.x = 2
	vec.x == 2
end

assert 'get y property' do
	vec = Vec3.new(5)
	vec.y == 5
end

assert 'set y property' do
	vec = Vec3.new(5)
	vec.y = 2
	vec.y == 2
end

assert 'get z property' do
	vec = Vec3.new(5)
	vec.z == 5
end

assert 'set z property' do
	vec = Vec3.new(5)
	vec.z = 2
	vec.z == 2
end

assert 'addition' do
	value = Vec3.new(0, 1, 0) + Vec3.new(1, 0, 0) + Vec3.new(0, 0, 1)
	value.x == 1 && value.y == 1 && value.z == 1
end

assert 'multiplication' do
	value = Vec3.new(1) * Vec3.new(3, 3, 3)
	value.x == 3 && value.y == 3 && value.z == 3
end

assert 'multiplication is not destructive' do
	original = Vec3.new(1)
	value = original * Vec3.new(3, 3, 3)
	original.x == 1 && original.y == 1 && original.z == 1
end

assert 'subtraction' do
	value = Vec3.new(3) - Vec3.new(2)
	value.x == 1 && value.y == 1 && value.z == 1
end