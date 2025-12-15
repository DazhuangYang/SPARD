import os
import shutil
import glob

def ensure_dir(path):
    if not os.path.exists(path):
        os.makedirs(path)

def move_exr_files(src_dir, dst_dir):
    ensure_dir(dst_dir)
    for exr_file in glob.glob(os.path.join(src_dir, '*.exr')):
        shutil.move(exr_file, os.path.join(dst_dir, os.path.basename(exr_file)))

def move_and_rename_jpeg_files(src_dir, pattern, dst_dir):
    ensure_dir(dst_dir)
    for jpeg_file in glob.glob(os.path.join(src_dir, pattern)):
        # Extract ***** part
        parts = os.path.basename(jpeg_file).split('.')
        if len(parts) >= 3:
            new_name = f"{parts[-2]}.jpg"
            shutil.move(jpeg_file, os.path.join(dst_dir, new_name))

def delete_remaining_jpeg(src_dir):
    for jpeg_file in glob.glob(os.path.join(src_dir, '*.jpeg')):
        os.remove(jpeg_file)

if __name__ == "__main__":
    base_dir = os.path.dirname(os.path.abspath(__file__))

    # 1. Move all .exr files to depth/
    move_exr_files(base_dir, os.path.join(base_dir, 'depth'))

    # 2. Move and rename FinalImage.*****.jpeg to color/*****.jpg
    move_and_rename_jpeg_files(
        base_dir,
        'FinalImage.*.jpeg',
        os.path.join(base_dir, 'color')
    )

    # 3. Move and rename FinalImageMovieRenderQueue_WorldNormal.*****.jpeg to normal/*****.jpg
    move_and_rename_jpeg_files(
        base_dir,
        'FinalImageMovieRenderQueue_WorldNormal.*.jpeg',
        os.path.join(base_dir, 'normal')
    )

    # 4. Delete remaining .jpeg files
    delete_remaining_jpeg(base_dir)

    # 5. Move traj.txt to base_dir
    traj_src = 'E:\\temp\\traj.txt'
    traj_dst = os.path.join(base_dir, 'traj.txt')

    shutil.move(traj_src, traj_dst)

    with open(os.path.join(base_dir, 'cam_info.yaml'), 'w') as f:
        f.write(
            "cam:\n"
            "  H: 720\n"
            "  W: 1280\n"
            "  fx: 531.2\n"
            "  fy: 531.2\n"
            "  cx: 640.0\n"
            "  cy: 360.0\n"
            "  depth_scale: 100.0 # cm2m for depth image in png format\n"
            "  crop_edge: 0\n"
            "bound: [[-0.6, 0.6],[-0.4, 0.1],[-0.6, 0.6]]\n"
        )
    
    print("Camera Intrinsics:")
    print("H: 720")
    print("W: 1280")
    print("fx: 531.2")
    print("fy: 531.2")
    print("cx: 640.0")
    print("cy: 360.0")

    # 6. Move color, depth, normal folders and cam_info.yaml, traj.txt to a new folder
    new_folder = os.path.join(base_dir, 'output')
    ensure_dir(new_folder)

    for item in ['color', 'depth', 'normal', 'cam_info.yaml', 'traj.txt']:
        src = os.path.join(base_dir, item)
        dst = os.path.join(new_folder, item)
        if os.path.isdir(src):
            shutil.move(src, dst)
        elif os.path.isfile(src):
            shutil.move(src, dst)

    