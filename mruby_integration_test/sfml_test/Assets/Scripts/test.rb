class Test
  DEGREES_PER_SECOND = 90

  def update(elapsed)

    @transform.rotation.y += elapsed * DEGREES_PER_SECOND
    @transform.rotation.y -= 360 while @transform.rotation.y > 360

  end
end