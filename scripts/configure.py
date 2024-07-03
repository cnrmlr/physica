import subprocess
import sys
import os
import csv

def install_package(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

def check_and_install_pyqt5():
    try:
        import PyQt5
        print("PyQt5 is already installed.")
    except ImportError:
        print("PyQt5 is not installed. Installing now...")
        install_package("PyQt5")
        print("PyQt5 installation complete.")

def create_config_folder(root_dir):
    config_folder = os.path.join(root_dir, 'config')
    if not os.path.exists(config_folder):
        os.makedirs(config_folder)
        print(f"{config_folder} folder created.")

def create_tsv_file(file_path):
    # Create (or clear) the file and write the header row
    with open(file_path, 'w', newline='') as file:
        writer = csv.writer(file, delimiter='\t')
        writer.writerow(['Initial Conditions', 'Transformation Rule'])
    print(f"{file_path} created or cleared.")

if __name__ == "__main__":
    check_and_install_pyqt5()

    # Get the root directory path (one level up from scripts directory)
    root_dir = os.path.abspath(os.path.join(os.getcwd(), os.pardir))

    # Create the config folder and tsv file within it
    create_config_folder(root_dir)
    tsv_file_path = os.path.join(root_dir, 'config', 'configuration.tsv')

    from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton, QVBoxLayout, QMessageBox

    class HypergraphGUI(QWidget):
        def __init__(self):
            super().__init__()
            self.initUI()

        def initUI(self):
            self.setWindowTitle('Hypergraph Initial Conditions and Transformation Rule')

            layout = QVBoxLayout()

            self.initial_conditions_label = QLabel('Initial Conditions:')
            self.initial_conditions_entry = QLineEdit(self)

            self.transformation_rule_label = QLabel('Transformation Rule:')
            self.transformation_rule_entry = QLineEdit(self)

            self.submit_button = QPushButton('Submit', self)
            self.submit_button.clicked.connect(self.submit)

            layout.addWidget(self.initial_conditions_label)
            layout.addWidget(self.initial_conditions_entry)
            layout.addWidget(self.transformation_rule_label)
            layout.addWidget(self.transformation_rule_entry)
            layout.addWidget(self.submit_button)

            self.setLayout(layout)

        def submit(self):
            initial_conditions = self.initial_conditions_entry.text()
            transformation_rule = self.transformation_rule_entry.text()

            # Write data to TSV file (clears the file and writes new content)
            with open(tsv_file_path, 'w', newline='') as file:
                writer = csv.writer(file, delimiter='\t')
                writer.writerow(['Initial Conditions', 'Transformation Rule'])
                writer.writerow([initial_conditions, transformation_rule])

            QMessageBox.information(self, 'Submitted', 'Initial conditions and transformation rule submitted successfully')
            
            # Close the GUI
            self.close()

    def main():
        app = QApplication(sys.argv)
        gui = HypergraphGUI()
        gui.show()
        sys.exit(app.exec_())

    main()
