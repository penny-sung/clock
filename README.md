

# 時鐘管理系統  

**國立虎尾科技大學 113 學年度第一學期**  
**課程：視窗程式設計**  
**組別：第 22 組**  
**組員：50915113 宋沛玲**  
**指導老師：林易泉**  

---

## 專題目的  

本專案旨在開發一個基於 Qt 框架的時鐘與計時器應用，結合日常生活中的實用性與易用性。系統的設計目標是提供使用者查看時間、進行倒數計時及設定鬧鐘的便捷工具，並以友善的介面設計提升用戶體驗。此外，透過本專案的開發，組員將能鞏固課堂所學的程式設計知識，並增進對 Qt 框架的理解與實踐能力。  

---

## 功能需求  

### 1. 時鐘功能  
- 即時時間顯示：顯示當前的「時、分、秒」。  
- 時間格式切換：支援 12 小時制與 24 小時制之間的切換，滿足不同使用者的需求。  

### 2. 計時器功能  
- 啟動計時：啟動倒數計時，顯示小時、分鐘、秒數。  
- 暫停與重置：使用者可隨時暫停計時，並可選擇重設倒數計時。  

### 3. 鬧鐘功能  
- 多個鬧鐘：使用者可新增多個鬧鐘，滿足不同的提醒需求。  
- 自訂鈴聲：支援使用者自訂鈴聲，使用內建的鈴聲或本地的音樂檔案作為鬧鐘提示音。  

---

## 系統架構  

### 1. 圖形使用者介面 (GUI)  
- 使用 Qt Designer 設計視覺界面。  
- 主要界面包含時鐘顯示頁面、計時器控制頁面及鬧鐘設置頁面，提供直觀的操作體驗。  

### 2. 邏輯控制 (Control Logic)  
- 時鐘更新：使用 QTimer 每秒觸發一次，更新時、分、秒的顯示，並支援 12/24 小時的切換控制。  
- 計時器控制：  
  - 啟動計時：每秒遞減倒數，並實時更新倒數時間的顯示。  
  - 暫停/重設：支援暫停計時，並可重設計時器回到初始狀態。  
- 鬧鐘控制：  
  - 鬧鐘的觸發條件為當前時間等於使用者設置的時間時，系統會播放指定的鈴聲提醒。  
  - 支援新增、刪除和編輯鬧鐘，並可上傳本地音樂檔案作為鈴聲。  

### 3. 資料儲存 (Data Storage)  
- 鬧鐘的設定（時間、鈴聲路徑等）會存儲在本地檔案中（如 JSON、SQLite 或 .ini 檔案）。  
- 系統在每次啟動時會自動加載本地儲存的鬧鐘資料，確保使用者的設定不會因為關閉程式而丟失。  


## 技術規劃  

| 功能           | 需求技術          | 說明                          |
|-----------------|-------------------|---------------------------------|
| 時鐘            | QTimer, QLabel     | 12/24 小時顯示與切換，時鐘秒秒更新 |
| 計時器          | QTimer, QPushButton | 啟動、暫停與重設計時功能         |
| 鬧鐘            | QTimer, QMediaPlayer, QDateTimeEdit | 支援多鬧鐘，並可自訂鈴聲           |
| 資料儲存        | QFile, QJsonDocument | 使用 JSON 格式保存鬧鐘的設定      |
| GUI 界面       | Qt Designer, PyQt5  | 設計 GUI 介面，支援使用者操作     |


## 操作說明  

1. **時鐘視圖**  
   - 啟動程式後，系統會自動顯示實時的時鐘。  
   - 點擊 12/24 小時切換按鈕，可在 12 小時制與 24 小時制之間切換顯示格式。  

2. **計時器視圖**  
   - 在「計時器」頁面，使用者可輸入計時目標時間，點擊啟動按鈕開始計時。  
   - 計時過程中，使用者可點擊暫停或重設計時器。  

3. **鬧鐘設定**  
   - 在「鬧鐘」頁面，點擊新增鬧鐘按鈕，設置鬧鐘的時間及鈴聲。  
   - 鬧鐘時間到達時，系統會播放鈴聲提醒使用者。  
   - 使用者可在此頁面編輯、刪除鬧鐘，並上傳自訂的鈴聲作為提示音。  

---
## 參考文獻
 - https://steam.oxxostudio.tw/category/python/pyqt5/qtimer.html
 - https://blog.51cto.com/xiaohaiwa/5378425
 - https://medium.com/bucketing/pyside2-tutorial-ch17-qtimeedit-qlcdnumber-analogclock-customize-ui-9951d101cbaa
 - https://www.evget.com/doclib/s/90/13956

