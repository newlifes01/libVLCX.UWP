using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Media.Devices;
using Windows.Storage;
using Windows.Storage.AccessCache;
using Windows.Storage.Pickers;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace SampleApp1
{
    public sealed partial class MainPage : Page
    {
        private libVLCX.Instance vlcInstance;

        /// <summary>
        /// Audio output device id
        /// </summary>
        private string audioDeviceId;

        private libVLCX.MediaPlayer vlcMediaPlayer;

        /// <summary>
        /// Get media duration
        /// </summary>
        private TimeSpan Duration => TimeSpan.FromMilliseconds(vlcMediaPlayer != null ? vlcMediaPlayer.length() : 0);

        /// <summary>
        /// Get media position
        /// </summary>
        private TimeSpan Position => TimeSpan.FromMilliseconds(vlcMediaPlayer != null ? vlcMediaPlayer.position() * vlcMediaPlayer.length() : 0);

        public MainPage()
        {
            this.InitializeComponent();

            swapChainPanel.CompositionScaleChanged += (s, e) => UpdateScale();
            swapChainPanel.SizeChanged += (s, e) => UpdateSize();

            this.Loaded += (sender, arg) =>
            {
                List<string> args = new List<string>
                {
                    "-I",
                    "dummy",
                    "--no-osd",
                    "--verbose=3",
                    "--no-stats",
                    "--avcodec-fast",
                    "--subsdec-encoding",
                    "--aout=winstore",
                    $"--keystore-file={Path.Combine(ApplicationData.Current.LocalFolder.Path, "keystore")}"
                };
                vlcInstance = new libVLCX.Instance(args, swapChainPanel);

                audioDeviceId = MediaDevice.GetDefaultAudioRenderId(AudioDeviceRole.Default);
                MediaDevice.DefaultAudioRenderDeviceChanged += (s, e) =>
                {
                    if (e.Role == AudioDeviceRole.Default)
                    {
                        audioDeviceId = e.Id;
                    }
                };

                UpdateScale();
            };
        }

        private void UpdateScale()
        {
            vlcInstance?.UpdateScale(swapChainPanel.CompositionScaleX, swapChainPanel.CompositionScaleY);
            UpdateSize();
        }

        private void UpdateSize()
        {
            var scp = swapChainPanel;
            vlcInstance?.UpdateSize((float)(scp.ActualWidth * scp.CompositionScaleX), (float)(scp.ActualHeight * scp.CompositionScaleY));
        }


        private void AppBarButton_Click(object sender, RoutedEventArgs e)
        {
            vlcMediaPlayer?.play();
        }

        private void AppBarButton_Click_1(object sender, RoutedEventArgs e)
        {
            vlcMediaPlayer?.pause();
        }

        private async void AppBarButton_Click_2(object sender, RoutedEventArgs e)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.ViewMode = PickerViewMode.List;
            picker.SuggestedStartLocation = PickerLocationId.VideosLibrary;
            picker.FileTypeFilter.Add("*");
            var file = await picker.PickSingleFileAsync();
            if (file != null)
            {
                OpenMediaFile(file);
            }
        }

        private void OpenMediaFile(StorageFile mediaFile)
        {
            string path = $"winrt://{StorageApplicationPermissions.FutureAccessList.Add(mediaFile)}";
            libVLCX.Media media = new libVLCX.Media(vlcInstance, path, libVLCX.FromType.FromPath);

            vlcMediaPlayer?.stop();
            vlcMediaPlayer = new libVLCX.MediaPlayer(media);
            vlcMediaPlayer.eventManager().OnPositionChanged += (s) => Debug.WriteLine($"{Position.ToString()} / {Duration.ToString()}");
            vlcMediaPlayer.setAudioOutput(audioDeviceId);
            vlcMediaPlayer.play();
        }
    }
}
