import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

file_path = 'SobelPrototyp\SobelPrototyp\Data\Histograms\histogram_cat.csv'
intensity_df = pd.read_csv(file_path, names=['intensity', 'count'])

sns.barplot(x='intensity', y='count', data=intensity_df, color='cyan')
plt.title('Histogram jasności obrazu')
plt.xlabel('Poziom intensywności (0-255)')
plt.ylabel('Liczba pikseli')
plt.xticks(range(0,256,50))
plt.show()

