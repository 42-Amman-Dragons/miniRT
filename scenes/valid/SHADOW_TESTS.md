# Hard-shadow test scenes

Build the project with `make`, then run each scene separately.

## Control: plane only

```sh
./miniRT scenes/valid/shadow_plane_control.rt
```

Expected: a smooth plane with no black dots or shadow acne.

## Sphere above a plane

```sh
./miniRT scenes/valid/shadow_sphere.rt
```

Expected: a red sphere with a detached, hard-edged shadow on the plane.

## Sphere touching a plane

```sh
./miniRT scenes/valid/shadow_contact.rt
```

Expected: the shadow begins directly beneath the sphere without a bright gap.

## Vertical cylinder

```sh
./miniRT scenes/valid/shadow_cylinder.rt
```

Expected: a blue cylinder casting a clean elongated shadow.

## Rotated cylinder

```sh
./miniRT scenes/valid/shadow_rotated_cylinder.rt
```

Expected: the cylinder and its shadow follow the diagonal cylinder axis.

## Multiple objects

```sh
./miniRT scenes/valid/shadow_multiple.rt
```

Expected: three independently shaded objects with clean shadows and no noise.

## Light positioned on a plane

```sh
./miniRT scenes/valid/shadow_light_on_plane.rt
```

Expected: two clean sphere shadows. The vertical plane containing the light must
not produce speckles or incorrectly shadow the floor.
