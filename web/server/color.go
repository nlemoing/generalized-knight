package main

import (
	"errors"
)

type Color struct {
	v1, v2, v3 int
}

func MakeColor(v1, v2, v3 int) Color {
	return Color{v1: v1, v2: v2, v3: v3}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func HslToHsv(c Color) (Color, error) {
	if c.v1 < 0 || c.v1 > 360 {
		return c, errors.New("Hue out of range")
	}
	if c.v2 < 0 || c.v2 > 100 {
		return c, errors.New("Saturation out of range")
	}
	if c.v3 < 0 || c.v3 > 100 {
		return c, errors.New("Lightness out of range")
	}
	v := c.v3 + ((c.v2 * min(c.v3, 100 - c.v3))/100)
	s := 0
	if v != 0 {
		s = 200 - (200 * c.v3/v)
	}
	c.v2 = s
	c.v3 = v
	return c, nil
}

func (c *Color) ToOpenCVRange() {
	c.v1 = c.v1 / 2
	c.v2 = (c.v2 * 255) / 100
	c.v3 = (c.v3 * 255) / 100
}
