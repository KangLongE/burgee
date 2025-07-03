package com.burgee.study.burgee1;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.io.File;
import java.io.IOException;
import java.util.Map;

@RestController
@CrossOrigin(origins = "*")
public class CCompilerController_point {

    @GetMapping("/submit-score")
    public ResponseEntity<String> runRankingProgram(@RequestParam("name") String name, @RequestParam("score") int score) {


        // C 코드 경로
        String cFilePath = "C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/point.c";
        String execPath = "C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/point_program";

        try {
            File cFile = new File(cFilePath);
            if (!cFile.exists()) {
                return ResponseEntity.badRequest().body("ranking.c 파일이 없습니다.");
            }
            // C 파일 컴파일 (Windows용 콘솔 프로그램 옵션 -mconsole 추가)
            Process compile = new ProcessBuilder("gcc", cFilePath, "-o", execPath, "-mconsole")
                    .redirectErrorStream(true)
                    .start();
            compile.waitFor();

            String compileOutput = new String(compile.getInputStream().readAllBytes());
            if (compile.exitValue() != 0) {
                return ResponseEntity.badRequest().body("컴파일 오류:\n" + compileOutput);
            }

            // 실행: score 값을 인자로 넘김
            String execFile = System.getProperty("os.name").toLowerCase().contains("win")
                    ? execPath + ".exe" : execPath;

            Process run = new ProcessBuilder(execFile,String.valueOf(score),name)
                    .redirectErrorStream(true)
                    .start();

            String output = new String(run.getInputStream().readAllBytes());
            run.waitFor();

            return ResponseEntity.ok(output);

        } catch (IOException | InterruptedException e) {
            return ResponseEntity.internalServerError().body("오류 발생: " + e.getMessage());
        }
    }
}