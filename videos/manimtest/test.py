import subprocess
try:
    subprocess.run(["ffmpeg", "-version"], check=True)
    print("✅ FFmpeg 已正确安装并可在命令行调用")
except FileNotFoundError:
    print("❌ FFmpeg 未找到，请检查 PATH 或重新安装")