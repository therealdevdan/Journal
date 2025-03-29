# Архитектура системы

## Компоненты
1. **Core**  
   - `SystemManager` - управление пользователями
   - `DataStorage` - хранение всех данных

2. **Модули**  
   - Администратор (CRUD операций)
   - Студент (просмотр данных)

## Диаграмма
```mermaid
graph TD
    A[SystemManager] --> B[Admin]
    A --> C[Student]
    B --> D[GradeSystem]
    C --> D
Copy

2. **`API.md`**  
```markdown
## API Endpoints (для будущего REST API)

### Admin
- `POST /api/grades` - добавление оценки  
Параметры:  
```json
{
  "student_id": "string",
  "subject": "math",
  "grade": 5
}
Copy

3. **`SCREENSHOTS/`**  
   - `main_menu.png` (пример интерфейса)
   - `admin_panel.png`

---

### 📂 `scripts/`
1. **`format_code.sh`**  
```bash
#!/bin/bash
# Форматирование кода clang-format
find src/ include/ -name *.hpp -o -name *.cpp | xargs clang-format -i
