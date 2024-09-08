/*void loadingBarAnimation() {
    const int totalProgress = 100; // Total progress value (e.g., 100%)
    const int barWidth = 50; // Width of the loading bar in characters

    for (int progress = 0; progress <= totalProgress; ++progress) {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < completedWidth) {
                cout << "=";
            } else {
                cout << " ";
            }
        }
        cout << "] " << progress << "%";
        cout.flush();

        // Add a small delay to control the speed of the animation
        Sleep(5);
    }

    cout << std::endl;
}*/
