

import pyaudio
import argparse

# parser = argparse.ArgumentParser()
# parser.add_argument("output_path", help="The name of the person to greet")
# args = parser.parse_args()


def equal_seperator():
    print("============================")


def hyphen_seperator():
    print("----------------------------")


def list_audio_devices():
    """Lists available audio devices"""
    p = pyaudio.PyAudio()
    info = p.get_host_api_info_by_index(0)
    num_devices = info.get('deviceCount')

    audio_devices = []
    for i in range(0, num_devices):
        if p.get_device_info_by_host_api_device_index(0, i).get('maxInputChannels') > 0:
            audio_devices.append(p.get_device_info_by_host_api_device_index(0, i).get('name'))

    p.terminate()
    return audio_devices


def print_to_console_with_emojis(audio_devices):
    """
    Prints the audio and video device information to the console with emojis.

    :param audio_devices: List of audio devices.
    :param video_devices: List of video devices.
    """
    microphone_emoji = "\U0001F3A4"  # Microphone emoji
    arrow_right_emoji = "\u2192"

    equal_seperator()
    print(f"{microphone_emoji} Audio Devices:")
    hyphen_seperator()

    for device in audio_devices:
        print(f"{microphone_emoji} {arrow_right_emoji} {device}")

    equal_seperator()


def write_device_info_to_file(audio_devices, filename=None):
    """
    Writes the audio and video device information to a specified file.

    :param audio_devices: List of audio devices.
    :param video_devices: List of video devices.
    :param filename: Name of the file to write the information to.
    """
    if filename is None:
        print_to_console_with_emojis(audio_devices)
        return
    with open(filename, 'w') as file:
        file.write("Audio Devices:\n")
        for device in audio_devices:
            file.write(f"{device}\n")


# Uncomment the line below to run the script
write_device_info_to_file(list_audio_devices())
