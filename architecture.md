# System Architecture
## Environment
- Has the properties of the environment
    - Atmospheric speed of sound field
    - Atmospheric density field
        - Atmosphere acoustic impedance (calculated from both of the above)
        - Z = density * speed_of_sound
    - Wind velocity field

## Entities
- Carries transform information (translation, orientation, scale)

## Illumination Source
- [Entity](#entities) with radiation pattern and intensity.

## Observers
- [Entity](#entities) with a sensitivity pattern.

## Materials
- Not sure yet if this should be a 3d material (basically a voxel material) or surface material...

## Objects
- An [entity](#entities) with geometry & [materials](#materials)

## Scenes
- Holds the [environment](#environment), [objects](#objects), [illumination sources](#illumination-source), and [observers](#observers)

## Ray Caster
- Casts rays through the [scene](#scenes) and computes a hit record for a ray.

## Renderer
- Uses a [ray caster](#ray-caster) to render a [scene](#scenes).
- Responsible for reserving memory for the frame buffer and combining the hit records into a frame.