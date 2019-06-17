# SettingsBinder

Библиотека имеет следующие возможности:
* готовые qt виджеты можно привязать к заданным переменным, что обеспечивает их автоматическое изменение при управлении виджетом и наоборот
* автоматическое сохранение заданных переменных 
* автоматическая загрузка заданных  переменных в программу и в привязанные виджеты

Длс наглядного представления можно клонировать репозиторий и открыть тестовый проект settingsbinder.pro

# Использование
Для использования возможностей библиотеки требуется выполнить следующие действия:
1. Склонировать проект в папку
2. Добавить в .pro файл своего проекта, например:
	<pre><code>
	include($$(SHARED_LIBS)/settingsbinder/settingsbinder.pri)
	</code></pre>
(если директория SHARED_LIBS записана в системных переменных, иначе просто выбрать путь)

3. Для записи переменных создать класс, унаследованный от BindedSettings
4. В унаследованном классе создать переменные следующим образом:
<pre><code>
	class Settings: public BindedSettings
	{
		Q_OBJECT
	public:
		Q_PROPERTY(QString stringForLe READ stringForLe WRITE setStringForLe NOTIFY stringForLeChanged)
		 //функция getter (возвращающая m_stringForLe)
		QString stringForLe() const;
		//функция setter (устанавливает m_stringForLe)
		void setStringForLe(const QString &stringForLe)
	signals:
		void stringForLeChanged(); 
	private:
		//переменная
		QString m_stringForLe;				
	}
</code></pre>
Данное действие удобно выполнить в среде QtCreator, создав переменную m_stringForLe, затем нажать правой кнопкой мыши на ней и выбрать "рефакторинг - установить методы получения и установки значения"

5. В классе интерфейса привязать виджет к переменной
	<pre><code>
		settings->bindWtToProp(ui->leString, "stringForLe");
			//первый аргумент - виджет, второй - значение из Q_PROPERTY
	</code></pre>
6. Для привязки enum class к поддерживаемому виджету требуется в унаследованном от BindedSettings классе написать следующее:
<pre><code>
class Settings: public BindedSettings
{
	Q_OBJECT
public:
	enum class States{
		state0 = 0,
		state1 = 1,
		state2 = 2
	};
	//Обязательно регистрируем наш класс в Q_ENUM
	Q_ENUM(States)											
	Q_PROPERTY(States stateForGrpb READ stateForGrpb WRITE setStateForGrpb NOTIFY stateForGrpbChanged)
	//функция getter (возвращающая state)
	Settings::States stateForGrpb() const;		
	//функция setter (устанавливает state)
	void setStateForGrpb(const States &stateForGrpb);		
	//обязательная функция для преобразования в QVariant
	Q_INVOKABLE QVariant stateForGrpbVariant(int val){		
		return getVariantEnumClass<States>(val);
	}
private:
	State m_state;	//переменная
</code></pre>

7. В классе интерфейса привязать QButtonGroup к переменной enum class
<pre><code>
	// создаём пустую группу кнопок
	btngrpStates = new QButtonGroup();	
	// добавляем кнопки, соответствующие значению enum class в int							
	btngrpStates->addButton(ui->radioButton, static_cast<int>(Settings::States::state0);           		
	btngrpStates->addButton(ui->radioButton_2, static_cast<int>(Settings::States::state1);          
	btngrpStates->addButton(ui->radioButton_3, static_cast<int>(Settings::States::state2);    
	//первый аргумент - виджет, второй - значение из Q_PROPERTY				
	settings->bindWtToProp(btngrpStates, "stateForGrpb");			
</code></pre>

8. Сохранение и загрузку данных осуществлять через save() и load() унаследованного от BindedSettings класса

# Особые случаи
1. Если требуется QLineEdit привязать данные формата HEX, то нужно в классе интерфейса добавить следующую строку перед привязкой:
<pre><code>
	settings->setIntTypePropertyTo(ui->leUintHex, Settings::IntType::hex);
</code></pre>
2. Если требуется сохранять и загружать переменные для класса, не унаследованного от BindedSettings, но унаследованного от QObject, то следует задать в нём переменные по тому же принципу(см п.4 пред. абзаца) и для сохранения и загрузки использовать объект класса SettingsSaver:
<pre><code>
	SettingsSaver* settingsSaver = new SettingsSaver(myObjectWithProperties);
	settingsSaver.load();
	settingsSaver.save();
</code></pre>

# Поддерживаемые привязки на текущий момент:
	QLineEdit - QString / uint (decimal) / uint (hex) / int / short / long / double 
	QComboBox - int/ enumclass
	QSpinBox - int / uint
	QDoubleSpinBox - double
	QCheckBox - bool
	QGroupButton - enum class / int
	