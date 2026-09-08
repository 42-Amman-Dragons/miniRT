# Anti-aliasing scene gallery

Run the scenes from the project root:

```sh
./miniRT scenes/valid/neon_gallery.rt
./miniRT scenes/valid/golden_hour.rt
./miniRT scenes/valid/cylinder_garden.rt
./miniRT scenes/valid/pastel_studio.rt
./miniRT scenes/valid/antialias_showcase.rt
```

`antialias_showcase.rt` has small spheres, narrow cylinders, diagonal rims, and
high-contrast boundaries. It is the clearest scene for comparing one sample per
pixel with 2x2 supersampling.

The other scenes emphasize composition, coloured ambient light, hard shadows,
overlapping silhouettes, cylinder caps, and curved highlights.
