# Spacecraft Pose Estimation and 3D Reconstruction Dataset (SPARD) Project

This Unreal Engine project serves as the simulation environment and dataset generator for the paper:

**NeRF-based simultaneous pose estimation and 3D reconstruction for non-cooperative space target**  
*Aerospace Science and Technology*, 2025.  
DOI: [10.1016/j.ast.2025.111010](https://doi.org/10.1016/j.ast.2025.111010)

## Overview

This project contains high-fidelity 3D models of space targets and Earth environments used to generate synthetic training and testing data for NeRF-based pose estimation and reconstruction algorithms.

## Prerequisites

- **Unreal Engine 5.3**
- Visual Studio 2022 (or compatible C++ compiler for UE5)

## Project Structure

### Maps (`/Content/`)
- **`space_earth.umap`**: Main simulation scene with Earth background.
- **`deep_space.umap`**: Deep space environment.
- **`small_4.umap`**: Additional test scene.

### Assets
- **Satellites**: Includes models for various satellites such as:
  - MRO
  - Proba-2
  - Ven
  - Smart Satellite 1A (SS1A)
- **Earth**: High-resolution 8k textures for Earth (Day, Night, Clouds, Normal, Specular) located in `/Content/earth/`.


## Usage

1.  Clone this repository.
2.  Open `s_claw.uproject` with Unreal Engine 5.3.
3.  Navigate to `Content/` to open the `deep_space` Level.
4.  Use the **Sequencer** `around_small_room4` to play back the cinematic sequences or render out image data.
5.  If you wish to test different satellite models, you can download them from [Google Drive](https://drive.google.com/file/d/1eCEIxt6zPekwF0-k0XgO2EjE1Mvk6CzH/view?usp=drive_link). After decompression, place it in the `/Content/` directory.

## Citation

If you use this dataset or project in your research, please cite the following paper:

```bibtex
@article{YourPaper2025,
  title = {NeRF-based simultaneous pose estimation and 3D reconstruction for non-cooperative space target},
  journal = {Aerospace Science and Technology},
  year = {2025},
  doi = {10.1016/j.ast.2025.111010},
  url = {https://doi.org/10.1016/j.ast.2025.111010}
}
```

## License

This project is provided for research purposes. Please refer to the paper for more details on usage rights and restrictions.

## Thanks
We would like to thank Chuan Yan for preparing the 3D models of space targets used in this UE project.