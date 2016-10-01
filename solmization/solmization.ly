\version "2.16.0" 

\score { 
	<< 
	\new Staff { 
		\new Voice { 
			\clef "bass" 
			d,4 b4 d'4 g,4 c'4 e'4 f4 a4 e4 a,4 
		}
		\addlyrics { 
			ut que -- ant lax -- is re -- son -- a -- re
		}
	}
	>> 

	\layout { 
		\context { 
		\Staff
			\remove Bar_engraver
			\remove Time_signature_engraver 
		}
	}
}
