import unittest
import i_love_lance_janice


class MyTestCase(unittest.TestCase):
    def test_answer(self):
        self.assertEqual("did you see last night's episode?",
                         i_love_lance_janice.answer("wrw blf hvv ozhg mrtsg'h vkrhlwv?"))
        self.assertEqual("did you see last night's episode?",
                         i_love_lance_janice.answer("wrw blf hvv ozhg mrtsg'h vkrhlwv?"))
        self.assertEqual("Yeah! I can't believe Lance lost his job at the colony!!",
                         i_love_lance_janice.answer("Yvzs! I xzm'g yvorvev Lzmxv olhg srh qly zg gsv xlolmb!!"))

