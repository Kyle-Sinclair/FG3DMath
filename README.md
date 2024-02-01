# FG3DMath
# State And Context

State And Context demonstraters have a blueprint defined Context Key - This Key represents
a combination of some sort of state, like above and behind, that is needed to "unlock" the demonstrators.
You could use this to build elaborate positioning  puzzles for example

# Interpolation

Pressing Left shift and Left Click will produce an interpolating "bullet", which will have it's RGB values and it's speed change over time

# Intersection Test

The Intersection Subsystem uses a ray cast from the third person camera manager as an intersectable.
The Intersecting demonstrator in the scene will have a force exerted on in the direction of the contact vector between the cameras
view and the sphere encasing it, allowing you to play a kind of psychic soccer

# Collisions

A very basic addition to the system. Each of the sphere colliders next to you when the PIE session starts have a different elasticity value,
that alters how much force is exerted upwards on it when it collides with the plain


# Noise

Pressing Left shift and Right click will make a "noisy" bullet, which sample Perlin noise to shift it's direction every frame.
Releasing many close together but spread out across the arena makes it clear how the sampled vector shifts slowing across the sample range

