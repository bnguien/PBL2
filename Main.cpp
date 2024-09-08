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
/*string getCurrentDate() {
    // Get the current time
    time_t now = time(nullptr);
    // Create a buffer to store the formatted date
    char buffer[80];
    // Format the current time as a string with the desired format
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtime(&now));
    // Convert the buffer to a string and return it
    return string(buffer);
}
*/