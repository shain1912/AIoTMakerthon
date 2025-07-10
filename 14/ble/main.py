

import os
import requests
from playwright.sync_api import sync_playwright

def extract_rnt_article(url):
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        page.goto(url)

        # 본문 텍스트 추출
        content = page.locator('#post-63505').inner_text()

        # 이미지들 추출
        images = page.locator('#post-63505 img').all()
        image_srcs = [img.get_attribute("src") for img in images]

        # 코드 블록 추출
        codes = page.locator('#post-63505 pre').all()
        code_blocks = [code.inner_text() for code in codes]

        browser.close()
        return {
            "text": content,
            "images": image_srcs,
            "codes": code_blocks
        }
if __name__ == "__main__":
    url = "https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/"
    result = extract_rnt_article(url)

    os.makedirs("images", exist_ok=True)
    for i, img_url in enumerate(result["images"]):
        try:
            img_data = requests.get(img_url).content
            with open(f"images/esp32_ble_{i+1}.png", "wb") as f:
                f.write(img_data)
        except Exception as e:
            print(f"[이미지 저장 실패] {img_url}: {e}")

    # 코드 저장
    os.makedirs("code_examples", exist_ok=True)
    for i, code in enumerate(result["codes"]):
        try:
            with open(f"code_examples/esp32_ble_{i+1}.txt", "w", encoding="utf-8") as f:
                f.write(code)
        except Exception as e:
            print(f"[코드 저장 실패] block {i+1}: {e}")

    # 리포트 저장
    os.makedirs(".taskmaster/reports", exist_ok=True)
    with open(".taskmaster/reports/task2-report.md", "w", encoding="utf-8") as f:
        f.write("# 📦 Task 2 크롤링 결과\n\n")
        f.write(f"**대상 URL**: {url}\n\n")
        f.write(f"- 이미지 수: {len(result['images'])}\n")
        f.write(f"- 코드 블록 수: {len(result['codes'])}\n")
        f.write("\n✅ 저장 위치:\n")
        f.write("- `/images/`\n")
        f.write("- `/code_examples/`\n")

    