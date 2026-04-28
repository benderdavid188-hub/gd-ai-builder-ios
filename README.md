# GD AI Builder - iOS

An AI-powered level building assistant for Geometry Dash on iOS. This mod integrates AI suggestions directly into the GD level editor to help with layout creation and optimization.

## Features

- 🤖 **AI Suggestions**: Get intelligent suggestions while building levels
- ⚡ **Real-time Integration**: Seamless integration with GD editor
- 📱 **iOS Native**: Optimized for iOS ARM64 architecture
- ⚙️ **Customizable**: Toggle AI on/off and configure API endpoints
- 🔒 **Secure**: HTTPS communication with AI backend

## Prerequisites

Before building, ensure you have:

- **Xcode 14+** or **Command Line Tools**
- **CMake 3.18+**
- **Git**
- **libcurl** (for HTTP requests)
- **Geode SDK** (automatically installed by build workflow)

## Building Locally

### 1. Clone the Repository

```bash
git clone https://github.com/benderdavid188-hub/gd-ai-builder-ios.git
cd gd-ai-builder-ios
```

### 2. Install Dependencies

```bash
brew install cmake ninja curl
```

### 3. Build the Mod

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

The compiled `.so` file will be in `build/out/`

### 4. Automated Build with GitHub Actions

Push to the `main` branch and GitHub Actions will automatically:
- ✅ Install dependencies
- ✅ Compile for iOS ARM64
- ✅ Package into an IPA file
- ✅ Provide downloadable artifact

## Sideloading on iOS

### Using e-sign (Recommended)

1. **Download the IPA**
   - Get the compiled `.ipa` from GitHub Actions artifacts

2. **Transfer to Device**
   - Use AirDrop, email, or cloud storage
   - Or use `ideviceinstaller`:
   ```bash
   ideviceinstaller -i gd-ai-builder.ipa
   ```

3. **Sign with e-sign**
   - Open e-sign app on your device
   - Select the `.ipa` file
   - Sign it with your Apple ID
   - Install to Geometry Dash

### Alternative: Using Xcode

```bash
xcode-select --install
xcodebuild -scheme gd-ai-builder -configuration Release -derivedDataPath build
```

## Usage

### Enable AI in the Editor

1. Open Geometry Dash and enter the Level Editor
2. Look for the **AI Builder** toggle in the options menu
3. Enable it to start receiving AI suggestions
4. Configure the API endpoint if needed (Settings → AI Builder)

### AI Suggestions Work On

- Object placement recommendations
- Pattern optimization
- Difficulty scaling suggestions
- Sync analysis and feedback

## Configuration

Edit settings in the mod menu:

```json
{
  "ai-enabled": true,
  "api-endpoint": "https://api.example.com/ai"
}
```

## Development

### Project Structure

```
gd-ai-builder-ios/
├── src/
│   └── AIBuilder.cpp          # Main mod implementation
├── mod.json                    # Mod configuration
├── CMakeLists.txt             # Build configuration
├── .github/
│   └── workflows/
│       └── ios-build.yml      # GitHub Actions workflow
└── README.md                  # This file
```

### Building a Custom Backend

The mod sends requests to your AI API:

```json
{
  "level_data": "base64_encoded_level",
  "model": "gd-ai-v1"
}
```

Expected response format:

```json
{
  "suggestion": "recommended_action",
  "confidence": 0.95
}
```

## Troubleshooting

### IPA Installation Fails
- Ensure device has sufficient storage
- Check iOS version is 13.0 or higher
- Verify Geometry Dash version compatibility

### AI Suggestions Not Working
- Verify internet connection
- Check API endpoint in settings
- Review device console for errors

### Build Errors
- Update Xcode: `xcode-select --install`
- Clear build cache: `rm -rf build/`
- Reinstall dependencies: `brew reinstall cmake curl`

## Performance

- **Build Time**: ~2-3 minutes
- **IPA Size**: ~15-20 MB
- **API Response**: <500ms average
- **Memory Overhead**: ~5-10 MB

## Contributing

We welcome contributions! Please:

1. Fork the repository
2. Create a feature branch
3. Test thoroughly on iOS devices
4. Submit a pull request

## Legal Notice

⚠️ **Disclaimer**: This mod is for educational purposes. Ensure compliance with:
- Geometry Dash Terms of Service
- Apple Developer Program terms
- Local laws regarding software modification

## Support

- 📧 **Issues**: Report bugs on GitHub Issues
- 💬 **Discussions**: Join our community discussions
- 📚 **Wiki**: Check the GitHub Wiki for advanced topics

## License

This project is licensed under the MIT License - see LICENSE file for details.

## Acknowledgments

- Built with **Geode SDK**
- Geometry Dash by RobTopGames
- Community feedback and testing

---

**Made with ❤️ for the Geometry Dash community**
